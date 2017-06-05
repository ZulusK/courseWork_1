//
// Created by Danil Kazimirov on 03.06.17.
//

#include <PersonRecognizer.h>
#include <Facecope.h>
#include <PersonFace.h>

PersonRecognizer::PersonRecognizer(const std::string &storagePath) {
    //todo
}

void PersonRecognizer::recognize(std::map<long, Face> persons) {
    for (auto it = persons.begin(); it != persons.end(); it++) {
        it->second.personFace->normalize();
        it->second.personFace->set_id(0);
    }
}