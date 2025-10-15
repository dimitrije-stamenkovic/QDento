#include "Issuer.h"
#include "Model/User.h"


Issuer::Issuer() : Issuer(User::company())
{}

Issuer::Issuer(const Company& company) :
    vat(company.vat),
    company_name{company.name},
    address{ company.address },
    identifier{ company.identifier },
    bank(company.bank),
    iban(company.iban),
    bic(company.bic)
{}
