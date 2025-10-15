#include "TileButton.h"
#include <QPainterPath>
#include <QMouseEvent>
#include "View/Theme.h"
#include <QApplication>
#include "View/Graphics/Zodiac.h"
#include "Model/FreeFunctions.h"
#include "Model/User.h"

TileButton::TileButton(QWidget* parent) : QAbstractButton(parent)
{
	header.setBold(1);
    header.setPointSizeF(info.pointSizeF()+6);

	infoLabel.setBold(true);

	this->installEventFilter(this);
}

void TileButton::paintEvent(QPaintEvent*)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::SmoothPixmapTransform);

	//getting the half-rounded button path:

	auto path = QPainterPath();
	
	path.addRoundedRect(this->rect(), 20, 20);

	if(m_reveresed) //transforming if reversed;
	{
		QTransform mirror(-1, 0, 0, 0, 1, 0, 0, 0, 1);
		painter.setTransform(mirror);
		painter.translate(-width(), 0);
	}

	painter.fillPath(path, Theme::sectionBackground);

	QPen pen(Theme::border);
	pen.setCosmetic(true);
	pen.setWidth(2);
	painter.setPen(pen);

	painter.drawPath(path);

	if (m_reveresed)
	{
		painter.resetTransform();
	}

	QColor textColor = hover && !clicked ?
		QColor(Theme::fontTurquoiseClicked)
		:
		QColor(Theme::fontTurquoise);

	painter.setPen(QPen(textColor));

	paintInfo(&painter);

	painter.end();
}

bool TileButton::eventFilter(QObject*, QEvent* e)
{
    if (e->type() == QEvent::Enter) {
		hover = true;
		QApplication::setOverrideCursor(QCursor(Qt::PointingHandCursor));
		update();
	}

    if (e->type() == QEvent::Leave) {
		QApplication::restoreOverrideCursor();
		hover = false;
		update();
	}

	if (e->type() == QEvent::MouseButtonPress)
	{
        if(static_cast<QMouseEvent*>(e)->button() == Qt::LeftButton)
        {
            clicked = true;
            update();
        }
	}

	if (e->type() == QEvent::MouseButtonRelease)
    {
        auto mouseEvent = static_cast<QMouseEvent*>(e);

        if(mouseEvent->button() == Qt::RightButton)
        {
            QApplication::restoreOverrideCursor();
            emit customContextMenuRequested(mapToGlobal(mouseEvent->pos()));
        }
        else
        {
            clicked = false;
            update();
        }
	}

	return false;
}

QString TileButton::elide(const QString& text, int length)
{
	if (text.length() < length)  return text;
	
	return text.chopped(text.length() - length) + "...";
}


PatientTile::PatientTile(QWidget* parent) : TileButton(parent)
{
	appointmentButton = new IconButton(this);
	appointmentButton->setIcon(QIcon(":/icons/icon_calendar.png"));
	appointmentButton->setFixedSize(iconSize, iconSize);
    appointmentButton->move(width() - (iconSize + 5), 5);
	appointmentButton->setToolTip(tr("Next appointment"));

    notificationButton = new IconButton(this);
    notificationButton->setIcon(QIcon(":/icons/icon_bell.png"));
    notificationButton->setFixedSize(iconSize, iconSize);
    notificationButton->move(appointmentButton->x()-40, appointmentButton->y());
    notificationButton->setToolTip(tr("Add reminder"));

    notesButton = new IconButton(this);
    notesButton->setIcon(QIcon(":/icons/icon_notes.png"));
    notesButton->setFixedSize(iconSize, iconSize);
    notesButton->move(notificationButton->x() - 40, notificationButton->y());
    notesButton->setToolTip(tr("Patient notes"));
}


void PatientTile::paintInfo(QPainter* painter)
{
    //int phonePosX = width() - fm.horizontalAdvance(phone) - 10;
    //int addressPosX = width() - fm.horizontalAdvance(address) - 10;

	constexpr int rowYPos[3]{ 60,80,100 };

	painter->setFont(infoLabel);
	painter->drawText(20, rowYPos[0], idLabel);
	painter->drawText(20, rowYPos[1], tr("Sex: ") );
	painter->drawText(20, rowYPos[2], tr("Date of birth: "));
	
	painter->drawText(width() / 2, rowYPos[0], tr("Phone number: "));
	painter->drawText(width() / 2, rowYPos[1], tr("Address: "));
	painter->drawText(width() / 2, rowYPos[2], tr("Age: "));

	QFontMetrics metric(infoLabel);

	auto horizontalAdvance = [metric](const QString& label) {
		return metric.horizontalAdvance(label);
	};

	painter->setFont(info);
	painter->drawText(20 + horizontalAdvance(idLabel), rowYPos[0], id);
	painter->drawText(20 + horizontalAdvance("Sex: "), rowYPos[1], sex);
	painter->drawText(20 + horizontalAdvance(tr("Date of birth: ")), rowYPos[2], birthDate);


	painter->drawText(width()/2 + horizontalAdvance(tr("Phone number: ")), rowYPos[0], phone);
	painter->drawText(width()/2 + horizontalAdvance(tr("Address: ")), rowYPos[1], address);
	painter->drawText(width() / 2 + horizontalAdvance(tr("Age: ")), rowYPos[2], age);
	
	painter->setFont(header);
	painter->setPen(hover && !clicked ? QPen(Theme::fontRedClicked) : QPen(QColor(Theme::fontRed)));

	painter->drawText(20, 27, name);

	painter->setRenderHint(QPainter::Antialiasing);

	if(zodiac) painter->drawPixmap(width()-37, height()-36, 32, 32, *zodiac);

	static QPixmap bdayPx{ ":/icons/icon_bday.png" };

    if (birthday) painter->drawPixmap(20 + horizontalAdvance(tr("Date of birth: ") + "00.00.0000   "), 86, 15, 15, bdayPx);
	
}

void PatientTile::resizeEvent(QResizeEvent* event)
{
	QWidget::resizeEvent(event);

    appointmentButton->move(width() - 5 - appointmentButton->width(), 5);
    notificationButton->move(appointmentButton->x()-40, appointmentButton->y());
    notesButton->move(notificationButton->x()-40, notificationButton->y());

	update();
}

void PatientTile::setData(const Patient& patient, int age)
{
	name = elide(QString::fromStdString(patient.firstLastName()), 30);

	idLabel = tr("SN: ");

	id = QString::fromStdString(patient.id);

	sex = (patient.sex == Patient::Sex::Male) ? tr("Male") : tr("Female");

	birthDate = QString::fromStdString((patient.birth.toLocalFormat()));

	this->age = QString::number(age);

    address = elide(QString::fromStdString(patient.address), 28);

	if (patient.phone != "")
		phone = QString::fromStdString(patient.phone);
	else phone = "";

	notesButton->setMonochrome(patient.patientNotes.empty());

	birthday = patient.birth.isSameDayInTheYear() && patient.birth.year != 1900;

	zodiac = Zodiac::getPixmap(patient.birth.day, patient.birth.month);

	update();
}