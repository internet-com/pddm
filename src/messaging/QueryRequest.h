/*
 * QueryRequest.h
 *
 *  Created on: May 17, 2016
 *      Author: edward
 */

#pragma once

#include <functional>

#include "MessageBody.h"
#include "../util/Money.h"

namespace pddm {
namespace messaging {

enum class QueryType {CURR_USAGE_SUM, CURR_USAGE_HISTOGRAM, AVAILABLE_OFFSET_BREAKDOWN, CUMULATIVE_USAGE, PROJECTED_SUM, PROJECTED_HISTOGRAM};

class QueryRequest: public MessageBody {
        using PriceFunction = std::function<Money (int)>;
    public:
        const QueryType request_type;
        const int time_window;
        const int query_number;
        const PriceFunction proposed_price_function;
        QueryRequest(const QueryType& request_type, const int time_window, const int query_number, const PriceFunction& proposed_price_function) :
            request_type(request_type), time_window(time_window), query_number(query_number), proposed_price_function(proposed_price_function) {}
         QueryRequest(const QueryType& request_type, const int time_window, const int query_number) :
             request_type(request_type), time_window(time_window), query_number(query_number) {}
};

} /* namespace messaging */
} /* namespace psm */
