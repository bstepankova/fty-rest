/*
Copyright (C) 2015 Eaton

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*!
 \file   cm-utils.h
 \brief  Header file for utility functions and helpers for computation module
 \author Karol Hrdina <KarolHrdina@eaton.com>
*/
#ifndef SRC_AGENTS_COMPUTATION_CM_UTILS_H__
#define SRC_AGENTS_COMPUTATION_CM_UTILS_H__

#include <map>
#include <string>
#include <tntdb/connect.h>

#include "ymsg.h"
#include "bios_agent.h"

namespace computation {

namespace web {

/*
 \brief Return weight of a sample at \a begin timestamp
 \param[in] timestamp of the sample
 \param[in] timestamp of the next sample
 \return weight of the sample at \a begin timestamp, -1 if \a begin >= \a end
*/ 
int64_t
sample_weight (int64_t begin, int64_t end);

void
solve_left_margin
(std::map <int64_t, double>& samples, int64_t extended_start);

int
calculate 
(std::map <int64_t, double>& samples, int64_t start, int64_t end, const char *type, double& result);

int
calculate_arithmetic_mean
(std::map <int64_t, double>& samples, int64_t start, int64_t end, double& result);

int
check_completeness
(int64_t last_container_timestamp, int64_t last_average_timestamp, int64_t end_timestamp, const char *step, int64_t& new_start);

int
request_averages
(tntdb::Connection& conn, int64_t element_id, const char *source, const char *type, const char *step, int64_t start_timestamp, int64_t end_timestamp,
 std::map<int64_t, double>& averages, std::string& unit, int64_t& last_average_timestamp, ymsg_t *message_out);

int
request_sampled
(tntdb::Connection& conn, int64_t element_id, const char *topic, int64_t start_timestamp, int64_t end_timestamp,
 std::map<int64_t, double>& samples, std::string& unit, ymsg_t *message_out);

} // namespace computation::web

} // namespace computation

#endif // SRC_AGENTS_COMPUTATION_CM_UTILS_H__
