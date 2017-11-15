//
// Copyright (C) 2016 OpenSim Ltd.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see http://www.gnu.org/licenses/.
//

//#include "inet/linklayer/ieee80211/mac/common/MacUtils.h"
#include "inet/linklayer/ieee80211/mac/contract/IRateControl.h"
#include "inet/linklayer/ieee80211/mac/Ieee80211Frame_m.h"
#include "inet/linklayer/ieee80211/mac/statistics/BasicStatistics.h"

namespace inet {
namespace ieee80211 {

Define_Module(BasicStatistics);

void BasicStatistics::initialize()
{
}

void BasicStatistics::finish()
{
//     transmit statistics
//    recordScalar("number of collisions", numCollision);
//    recordScalar("number of internal collisions", numInternalCollision);
//    for (int i = 0; i < numCategories(); i++) {
//        std::stringstream os;
//        os << i;
//        std::string th = "number of retry for AC " + os.str();
//        recordScalar(th.c_str(), numRetry(i));
//    }
//    recordScalar("sent and received bits", numBits);
//    for (int i = 0; i < numCategories(); i++) {
//        std::stringstream os;
//        os << i;
//        std::string th = "sent packet within AC " + os.str();
//        recordScalar(th.c_str(), numSent(i));
//    }
//    recordScalar("sent in TXOP ", numSentTXOP);
//    for (int i = 0; i < numCategories(); i++) {
//        std::stringstream os;
//        os << i;
//        std::string th = "sentWithoutRetry AC " + os.str();
//        recordScalar(th.c_str(), numSentWithoutRetry(i));
//    }
//    for (int i = 0; i < numCategories(); i++) {
//        std::stringstream os;
//        os << i;
//        std::string th = "numGivenUp AC " + os.str();
//        recordScalar(th.c_str(), numGivenUp(i));
//    }
//    for (int i = 0; i < numCategories(); i++) {
//        std::stringstream os;
//        os << i;
//        std::string th = "numDropped AC " + os.str();
//        recordScalar(th.c_str(), numDropped(i));
//    }
}

}  // namespace ieee80211
}  // namespace inet

