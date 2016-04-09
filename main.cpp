#include "QJSTP.h"
#include "iostream"

int main() {
    QScriptValue val = QJSTP::parse("{\n"
                                    "  name: 'Marcus Aurelius',\n"
                                    "  passport: 'AE127095',\n"
                                    "  birth: {\n"
                                    "    date: '1990-02-15',\n"
                                    "    place: 'Rome'\n"
                                    "  },\n"
                                    "  contacts: {\n"
                                    "    email: 'marcus@aurelius.it',\n"
                                    "    phone: '+380505551234',\n"
                                    "    address: {\n"
                                    "      country: 'Ukraine',\n"
                                    "      city: 'Kiev',\n"
                                    "      zip: '03056',\n"
                                    "      street: 'Pobedy',\n"
                                    "      building: '37',\n"
                                    "      floor: '1',\n"
                                    "      room: '158'\n"
                                    "    }\n"
                                    "  }\n"
                                    "}");
    std::cout << val.toString().toStdString();
    return 0;
}
