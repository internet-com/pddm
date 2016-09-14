/*
 * AgreementValue.h
 *
 *  Created on: May 26, 2016
 *      Author: edward
 */

#pragma once

#include <ostream>

#include "MessageBody.h"
#include "SignedValue.h"
#include "../util/CryptoLibrary.h"

namespace pddm {

namespace messaging {

struct AgreementValue : public MessageBody {
        SignedValue signed_value;
        /** The ID of the node that signed the SignedValue (after accepting it). */
        int accepter_id;
        /** The signature over the entire SignedValue of a node that accepted the value. */
        util::SignatureArray accepter_signature;
        AgreementValue(const SignedValue& signed_value, const int accepter_id) :
            signed_value(signed_value), accepter_id(accepter_id) {}
        virtual ~AgreementValue() = default;
        inline bool operator==(const MessageBody& _rhs) const {
            if (auto* rhs = dynamic_cast<const AgreementValue*>(&_rhs))
                return this->signed_value == rhs->signed_value
                        && this->accepter_id == rhs->accepter_id
                        && this->accepter_signature == rhs->accepter_signature;
            else return false;
        }
};

inline std::ostream& operator<<(std::ostream& out, const AgreementValue val) {
    return out << "{AgreementValue: " << val.signed_value << " accepted by " << val.accepter_id << "}";
}


}  // namespace messaging

}  // namespace pddm


