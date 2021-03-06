/*
 * QueryRequest.h
 *
 *  Created on: May 17, 2016
 *      Author: edward
 */

#pragma once

#include <functional>
#include <mutils-serialization/SerializationSupport.hpp>

#include "Message.h"
#include "MessageType.h"
#include "../util/Money.h"

namespace pddm {
namespace messaging {

enum class QueryType {CURR_USAGE_SUM, CURR_USAGE_HISTOGRAM, AVAILABLE_OFFSET_BREAKDOWN, CUMULATIVE_USAGE, PROJECTED_SUM, PROJECTED_HISTOGRAM};

std::ostream& operator<<(std::ostream& out, const QueryType& type);

constexpr bool is_single_valued_query(const QueryType& query_type) {
    return query_type == QueryType::CURR_USAGE_SUM || query_type == QueryType::CUMULATIVE_USAGE || query_type == QueryType::PROJECTED_SUM;
}

class QueryRequest: public Message {
    public:
        using PriceFunction = std::function<Money (int)>;
        static const constexpr MessageType type = MessageType::QUERY_REQUEST;
        const QueryType request_type;
        const int time_window;
        const int query_number;
        const PriceFunction proposed_price_function;
        QueryRequest(const QueryType& request_type, const int time_window, const int query_number,
                const PriceFunction& proposed_price_function = PriceFunction{}) :
            Message(UTILITY_NODE_ID, nullptr), //hack, these fields should really be the body of the message. Would it hurt to make a QueryRequestMessageBody?
            request_type(request_type),
            time_window(time_window),
            query_number(query_number),
            proposed_price_function(proposed_price_function) {}
        virtual ~QueryRequest() = default;
//        inline bool operator==(const Message& _rhs) const {
//            if (auto* rhs = dynamic_cast<const QueryRequest*>(&_rhs))
//                return this->request_type == rhs->request_type
//                        && this->time_window == rhs->time_window
//                        && this->query_number == rhs->query_number;
//            else return false;
//        }
        std::size_t bytes_size() const;
        std::size_t to_bytes(char* buffer) const;
        void post_object(const std::function<void (char const * const,std::size_t)>& consumer) const;
        static std::unique_ptr<QueryRequest> from_bytes(mutils::DeserializationManager<>* m, const char* buffer);
};

std::ostream& operator<<(std::ostream& out, const QueryRequest& qr);

struct QueryNumLess {
        bool operator()(const QueryRequest& lhs, const QueryRequest& rhs) const {
            return lhs.query_number < rhs.query_number;
        }
};

struct QueryNumGreater {
        bool operator()(const QueryRequest& lhs, const QueryRequest& rhs) const {
            return lhs.query_number > rhs.query_number;
        }
};

} /* namespace messaging */
} /* namespace psm */

