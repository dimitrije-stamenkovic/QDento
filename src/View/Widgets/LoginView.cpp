#include "LoginView.h"
#include <QPainter>
#include "Presenter/LoginPresenter.h"
#include "View/Theme.h"
#include <QApplication>
#include <QScreen>

LoginView::LoginView(LoginPresenter& p, QWidget *parent)
    : QDialog(parent), presenter(p)
{
	ui.setupUi(this);

	setModal(true);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
	setWindowTitle(tr("Login"));

    move(QGuiApplication::screens().at(0)->geometry().center() - frameGeometry().center());

	ui.passEdit->setEchoMode(QLineEdit::Password);

    connect(ui.okButton, &QPushButton::clicked, this, [&]{

			if (!ui.doctorCombo->count()) return;

                presenter.okPressed(
						ui.passEdit->text().toStdString(),
						ui.rememberCheck->isChecked()
				);

		}
	);

	connect(ui.doctorCombo, &QComboBox::currentIndexChanged, this, [&](int idx) { 
		presenter.userIdxChanged(idx); 
	});

	presenter.setView(this);
}

void LoginView::setDentistList(const std::vector<std::string>& doctorList)
{
	ui.doctorCombo->clear();

	for (auto& d : doctorList) {
		ui.doctorCombo->addItem(d.c_str());
	}

	if (!ui.doctorCombo->count()) {
		return;
	}

	ui.doctorCombo->setCurrentIndex(0);
	emit ui.doctorCombo->currentIndexChanged(0);
}

void LoginView::disablePasswordField(bool disabled)
{
	ui.passEdit->clear();
	ui.passEdit->setPlaceholderText(disabled ? tr("No Password") : "");
	ui.passEdit->setMaxLength(disabled ? 0 : 20);

	if (!disabled) {
		ui.passEdit->setFocus();
	}
}

void LoginView::paintEvent(QPaintEvent*)
{
	QPainter painter;
	painter.begin(this);
	painter.fillRect(QRect(0, 0, width(), height()), Qt::white);
	painter.end();
}

LoginView::~LoginView()
{
}
