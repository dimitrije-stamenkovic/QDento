#include "Recipient.h"
#include "Model/UserStructs.h"
#include "Model/Patient.h"
#include <array>

Recipient::Recipient(const Patient& patient) :
    name{ patient.firstLastName() } ,
    address{ patient.address },
    identifier{ patient.id },
    phone {patient.phone}
{}
