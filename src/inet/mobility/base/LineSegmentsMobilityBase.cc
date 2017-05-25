//
// Copyright (C) 2005 Andras Varga
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#include "inet/mobility/base/LineSegmentsMobilityBase.h"
#include "inet/common/INETMath.h"

namespace inet {

LineSegmentsMobilityBase::LineSegmentsMobilityBase()
{
    targetPosition = Coord::ZERO;
}

void LineSegmentsMobilityBase::initialize(int stage)
{
    MovingMobilityBase::initialize(stage);
    EV_TRACE << "initializing LineSegmentsMobilityBase stage " << stage << endl;
    if (stage == INITSTAGE_LOCAL) {
        WATCH(targetPosition);
        WATCH(segmentStartPosition);
        WATCH(segmentStartTime);
    }
}

void LineSegmentsMobilityBase::initializePosition()
{
    MobilityBase::initializePosition();
    simtime_t now = simTime();
    if (!stationary) {
        doSetTargetPosition();
    }
    lastUpdate = now;
    scheduleUpdate();
}

void LineSegmentsMobilityBase::move()
{
    simtime_t now = simTime();
    if (now == nextChange) {
        lastPosition = targetPosition;
        lastUpdate = now;
        EV_INFO << "reached current target position = " << lastPosition << endl;
        doSetTargetPosition();
    }
    else if (now > lastUpdate) {
        ASSERT(nextChange == -1 || now < nextChange);
        if (nextChange == -1 ) {
            lastPosition = segmentStartPosition + lastSpeed * (now - segmentStartTime).dbl();
        }
        else {
            double alpha = (now - segmentStartTime) / (nextChange - segmentStartTime);  //FIXME case of nextChange == -1
            lastPosition = segmentStartPosition * (1 - alpha) + targetPosition * alpha;
        }
        lastUpdate = now;
    }
}

void LineSegmentsMobilityBase::doSetTargetPosition()
{
    setTargetPosition();
    segmentStartPosition = lastPosition;
    segmentStartTime = simTime();
    lastSpeed = (nextChange == -1.0) ? Coord::ZERO : (targetPosition - segmentStartPosition) / (nextChange - segmentStartTime).dbl();
    EV_INFO << "current target position = " << targetPosition << ", next change = " << nextChange << endl;
}

} // namespace inet

