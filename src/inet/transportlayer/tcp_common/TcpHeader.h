//
// Copyright (C) 2004 Andras Varga
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
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#ifndef __INET_TCPSEGMENT_H
#define __INET_TCPSEGMENT_H

#include <list>

#include "inet/common/INETDefs.h"
#include "inet/transportlayer/tcp_common/TcpHeader_m.h"

namespace inet {

namespace tcp {

/** @name Comparing sequence numbers */
//@{
inline bool seqLess(uint32 a, uint32 b) { return a != b && (b - a) < (1UL << 31); }
inline bool seqLE(uint32 a, uint32 b) { return (b - a) < (1UL << 31); }
inline bool seqGreater(uint32 a, uint32 b) { return a != b && (a - b) < (1UL << 31); }
inline bool seqGE(uint32 a, uint32 b) { return (a - b) < (1UL << 31); }
inline uint32 seqMin(uint32 a, uint32 b) { return ((b - a) < (1UL << 31)) ? a : b; }
inline uint32 seqMax(uint32 a, uint32 b) { return ((a - b) < (1UL << 31)) ? a : b; }
//@}

/**
 * Represents a TCP segment. More info in the TcpHeader.msg file
 * (and the documentation generated from it).
 */
class INET_API TcpHeader : public TcpHeader_Base
{
  protected:
    typedef std::vector<TcpOption *> OptionList;
    OptionList headerOptionList;

  private:
    void copy(const TcpHeader& other);
    void clean();

  public:
    TcpHeader() : TcpHeader_Base() {}
    TcpHeader(const TcpHeader& other) : TcpHeader_Base(other) { copy(other); }
    ~TcpHeader();
    TcpHeader& operator=(const TcpHeader& other);
    virtual TcpHeader *dup() const override { return new TcpHeader(*this); }
    virtual void parsimPack(cCommBuffer *b) const override;
    virtual void parsimUnpack(cCommBuffer *b) override;

    /**
     * Returns RFC 793 specified SEG.LEN:
     *     SEG.LEN = the number of octets occupied by the data in the segment
     *               (counting SYN and FIN)
     *
     */
    uint32_t getSynFinLen() const { return (finBit ? 1 : 0) + (synBit ? 1 : 0); }

    // manage header options:

    /** Calculate Length of TCP Options Array in bytes */
    virtual unsigned short getHeaderOptionArrayLength();

    /** Generated but unused method, should not be called. */
    virtual void setHeaderOptionArraySize(size_t size) override;

    /** Returns the number of TCP options in this TCP segment */
    virtual size_t getHeaderOptionArraySize() const override;

    /** Returns the kth TCP options in this TCP segment */
    virtual TcpOption *getHeaderOptionForUpdate(size_t k) override  { handleChange(); return headerOptionList.at(k); }

    virtual const TcpOption *getHeaderOption(size_t k) const override  { return headerOptionList.at(k); }

    /** Generated but unused method, should not be called. */
    virtual void setHeaderOption(size_t k, TcpOption* headerOption) override;

    /** Adds a TCP option to the TCP segment */
    virtual void insertHeaderOption(TcpOption *headerOption) override;
    virtual void insertHeaderOption(size_t k, TcpOption *headerOption) override { throw cRuntimeError("Do not use it!"); }

    /** Adds a TCP option to the TCP segment */
    virtual void eraseHeaderOption(size_t k) override { throw cRuntimeError("Do not use it!"); }

    /** Drops all TCP options of the TCP segment */
    virtual void dropHeaderOptions();


    virtual unsigned int getSourcePort() const override { return TcpHeader_Base::getSrcPort(); }
    virtual void setSourcePort(unsigned int port) override { TcpHeader_Base::setSrcPort(port); }
    virtual unsigned int getDestinationPort() const override { return TcpHeader_Base::getDestPort(); }
    virtual void setDestinationPort(unsigned int port) override { TcpHeader_Base::setDestPort(port); }
};

} // namespace tcp

} // namespace inet

#endif // ifndef __INET_TCPSEGMENT_H

