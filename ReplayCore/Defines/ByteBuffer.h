#ifndef _BYTEBUFFER_H
#define _BYTEBUFFER_H

#include "Common.h"
#include "ByteConverter.h"

#include <string>
#include <vector>
#include <list>
#include <map>
#include <sstream>

class ByteBufferException
{
    public:
        ByteBufferException(bool _add, size_t _pos, size_t _esize, size_t _size)
            : add(_add), pos(_pos), esize(_esize), size(_size)
        {
            PrintPosError();
        }

        void PrintPosError() const
        {
            printf("Attempted to %s in ByteBuffer (pos: %u size: %u) value with size: %u",
                (add ? "put" : "get"), pos, size, esize);
        }
    private:
        bool add;
        size_t pos;
        size_t esize;
        size_t size;
};

template<class T>
struct Unused
{
    Unused() {}
};

class ByteBuffer
{
    public:
        static size_t const DEFAULT_SIZE = 0x1000;
        static uint8 const InitialBitPos = 8;

        // constructor
        ByteBuffer(): _rpos(0), _wpos(0), _bitpos(InitialBitPos), _curbitval(0)
        {
            _storage.reserve(DEFAULT_SIZE);
        }

        // constructor
        ByteBuffer(size_t res): _rpos(0), _wpos(0), _bitpos(InitialBitPos), _curbitval(0)
        {
            _storage.reserve(res);
        }

        // copy constructor
        ByteBuffer(ByteBuffer const& buf): _rpos(buf._rpos), _wpos(buf._wpos),
            _bitpos(buf._bitpos), _curbitval(buf._curbitval), _storage(buf._storage) { }

        // move constructor
        ByteBuffer(ByteBuffer&& buf) : _rpos(buf._rpos), _wpos(buf._wpos),
            _bitpos(buf._bitpos), _curbitval(buf._curbitval), _storage(std::move(buf._storage)) {}

        // move operator
        ByteBuffer& operator=(ByteBuffer&& rhs)
        {
            _rpos = rhs._rpos;
            _wpos = rhs._wpos;
            _bitpos = rhs._bitpos;
            _curbitval = rhs._curbitval;
            _storage = std::move(rhs._storage);
            return *this;
        }

        void clear()
        {
            _storage.clear();
            _rpos = _wpos = 0;
        }

        template <typename T> void put(size_t pos,T value)
        {
            #ifdef _WIN32
            EndianConvert(value);
            #endif
            put(pos,(uint8*)&value,sizeof(value));
        }

        void FlushBits()
        {
            if (_bitpos == 8)
                return;

            _bitpos = 8;

            append((uint8 *)&_curbitval, sizeof(uint8));
            _curbitval = 0;
        }

        bool WriteBit(uint32 bit)
        {
            --_bitpos;
            if (bit)
                _curbitval |= (1 << (_bitpos));

            if (_bitpos == 0)
            {
                _bitpos = 8;
                append((uint8 *)&_curbitval, sizeof(_curbitval));
                _curbitval = 0;
            }

            return (bit != 0);
        }

        bool ReadBit()
        {
            if (_bitpos >= 8)
            {
                read(&_curbitval, 1);
                _bitpos = 0;
            }

            return ((_curbitval >> (8 - ++_bitpos)) & 1) != 0;
        }

        void WriteBits(uint64 value, int32 bits)
        {
            // remove bits that don't fit
            value &= (1 << bits) - 1;
            value &= (uint64(1) << bits) - 1;

            if (bits > int32(_bitpos))
            {
                // first write to fill bit buffer
                _curbitval |= value >> (bits - _bitpos);
                bits -= _bitpos;
                _bitpos = 8; // required "unneccessary" write to avoid double flushing
                append(&_curbitval, sizeof(_curbitval));

                // then append as many full bytes as possible
                while (bits >= 8)
                {
                    bits -= 8;
                    append<uint8>(value >> bits);
                }

                // store remaining bits in the bit buffer
                _bitpos = 8 - bits;
                _curbitval = (value & ((1 << bits) - 1)) << _bitpos;
                _curbitval = (value & ((uint64(1) << bits) - 1)) << _bitpos;
            }
            else
            {
                // entire value fits in the bit buffer
                _bitpos -= bits;
                _curbitval |= value << _bitpos;

                if (_bitpos == 0)
                {
                    _bitpos = 8;
                    append(&_curbitval, sizeof(_curbitval));
                    _curbitval = 0;
                }
            }
        }

        uint32 ReadBits(int32 bits)
        {
            uint32 value = 0;
            for (int32 i = bits - 1; i >= 0; --i)
                value |= uint32(ReadBit()) << i;

            return value;
        }

        // Reads a byte (if needed) in-place
        void ReadByteSeq(uint8& b)
        {
            if (b != 0)
                b ^= read<uint8>();
        }

        void WriteByteSeq(uint8 b)
        {
            if (b != 0)
                append<uint8>(b ^ 1);
        }

        ByteBuffer& operator<<(uint8 value)
        {
            append<uint8>(value);
            return *this;
        }

        ByteBuffer& operator<<(uint16 value)
        {
            append<uint16>(value);
            return *this;
        }

        ByteBuffer& operator<<(uint32 value)
        {
            append<uint32>(value);
            return *this;
        }

        ByteBuffer& operator<<(uint64 value)
        {
            append<uint64>(value);
            return *this;
        }

#ifdef __MINGW32__
        ByteBuffer& operator<<(time_t value)
        {
            append<time_t>(value);
            return *this;
        }
#endif

        // signed as in 2e complement
        ByteBuffer& operator<<(int8 value)
        {
            append<int8>(value);
            return *this;
        }

        ByteBuffer& operator<<(int16 value)
        {
            append<int16>(value);
            return *this;
        }

        ByteBuffer& operator<<(int32 value)
        {
            append<int32>(value);
            return *this;
        }

        ByteBuffer& operator<<(int64 value)
        {
            append<int64>(value);
            return *this;
        }

        // floating points
        ByteBuffer& operator<<(float value)
        {
            append<float>(value);
            return *this;
        }

        ByteBuffer& operator<<(double value)
        {
            append<double>(value);
            return *this;
        }

        ByteBuffer& operator<<(std::string const& value)
        {
            append((uint8 const *)value.c_str(), value.length());
            append((uint8)0);
            return *this;
        }

        ByteBuffer& operator<<(char const* str)
        {
            append((uint8 const *)str, str ? strlen(str) : 0);
            append((uint8)0);
            return *this;
        }

        ByteBuffer& operator<<(bool const& val)
        {
            append((uint8 const *)&val, 1);
            return *this;
        }

        ByteBuffer& operator>>(bool& value)
        {
            value = read<char>() > 0 ? true : false;
            return *this;
        }

        ByteBuffer& operator>>(uint8& value)
        {
            value = read<uint8>();
            return *this;
        }

        ByteBuffer& operator>>(uint16& value)
        {
            value = read<uint16>();
            return *this;
        }

        ByteBuffer& operator>>(uint32& value)
        {
            value = read<uint32>();
            return *this;
        }

        ByteBuffer& operator>>(uint64& value)
        {
            value = read<uint64>();
            return *this;
        }

#ifdef __MINGW32__
        ByteBuffer& operator >> (time_t& value)
        {
            value = read<time_t>();
            return *this;
        }
#endif

        //signed as in 2e complement
        ByteBuffer& operator>>(int8& value)
        {
            value = read<int8>();
            return *this;
        }

        ByteBuffer& operator>>(int16& value)
        {
            value = read<int16>();
            return *this;
        }

        ByteBuffer& operator>>(int32& value)
        {
            value = read<int32>();
            return *this;
        }

        ByteBuffer& operator>>(int64& value)
        {
            value = read<int64>();
            return *this;
        }

        ByteBuffer& operator>>(float& value)
        {
            value = read<float>();
            return *this;
        }

        ByteBuffer& operator>>(double& value)
        {
            value = read<double>();
            return *this;
        }

        ByteBuffer& operator>>(std::string& value)
        {
            value.clear();
            while (rpos() < size())                         // prevent crash at wrong string format in packet
            {
                char c = read<char>();
                if (c == 0)
                    break;
                value += c;
            }
            return *this;
        }

        template<class T>
        ByteBuffer& operator>>(Unused<T> const&)
        {
            read_skip<T>();
            return *this;
        }


        uint8 operator[](size_t pos) const
        {
            return read<uint8>(pos);
        }

        size_t rpos() const { return _rpos; }

        size_t rpos(size_t rpos_)
        {
            _rpos = rpos_;
            return _rpos;
        }

        size_t wpos() const { return _wpos; }

        size_t wpos(size_t wpos_)
        {
            _wpos = wpos_;
            return _wpos;
        }

        /// Returns position of last written bit
        size_t bitwpos() const { return _wpos * 8 + 8 - _bitpos; }

        size_t bitwpos(size_t newPos)
        {
            _wpos = newPos / 8;
            _bitpos = 8 - (newPos % 8);
            return _wpos * 8 + 8 - _bitpos;
        }

        template<typename T>
        void read_skip() { read_skip(sizeof(T)); }

        void read_skip(size_t skip)
        {
            if(_rpos + skip > size())
                throw ByteBufferException(false, _rpos, skip, size());
            _rpos += skip;
        }

        void rfinish()
        {
            _rpos = wpos();
        }

        template <typename T> T read()
        {
            T r = read<T>(_rpos);
            _rpos += sizeof(T);
            return r;
        }

        template <typename T> T read(size_t pos) const
        {
            if(pos + sizeof(T) > size())
                throw ByteBufferException(false, pos, sizeof(T), size());
            T val = *((T const*)&_storage[pos]);
            #ifdef _WIN32
            EndianConvert(val);
            #endif
            return val;
        }

        void read(uint8* dest, size_t len)
        {
            if(_rpos  + len > size())
                throw ByteBufferException(false, _rpos, len, size());
            memcpy(dest, &_storage[_rpos], len);
            _rpos += len;
        }

        uint64 readPackGUID()
        {
            uint64 guid = 0;
            uint8 guidmark = 0;
            (*this) >> guidmark;

            for(int i = 0; i < 8; ++i)
            {
                if(guidmark & (uint8(1) << i))
                {
                    uint8 bit;
                    (*this) >> bit;
                    guid |= (uint64(bit) << (i * 8));
                }
            }

            return guid;
        }

        std::string ReadString(uint32 length)
        {
            if (!length)
                return std::string();
            char* buffer = new char[length + 1]();
            read((uint8*)buffer, length);
            std::string retval = buffer;
            delete[] buffer;
            return retval;
        }

        //! Method for writing strings that have their length sent separately in packet
        //! without null-terminating the string
        void WriteString(std::string const& str)
        {
            if (size_t len = str.length())
                append(str.c_str(), len);
        }

        uint8 const* contents() const { return &_storage[0]; }

        size_t size() const { return _storage.size(); }
        bool empty() const { return _storage.empty(); }

        void resize(size_t newsize)
        {
            _storage.resize(newsize);
            _rpos = 0;
            _wpos = size();
        }

        void reserve(size_t ressize)
        {
            if (ressize > size())
                _storage.reserve(ressize);
        }

        void append(std::string const& str)
        {
            append((uint8 const*)str.c_str(), str.size() + 1);
        }

        void append(std::vector<uint8> const& src) 
        {
            return append(src.data(), src.size());
        }

        void append(char const* src, size_t cnt)
        {
            return append((uint8 const*)src, cnt);
        }

        template<class T> void append(T const* src, size_t cnt)
        {
            return append((uint8 const*)src, cnt * sizeof(T));
        }

        void append(uint8 const* src, size_t cnt)
        {
            if (!cnt)
                return;

            assert(size() < 10000000);

            if (_storage.size() < _wpos + cnt)
                _storage.resize(_wpos + cnt);
            memcpy(&_storage[_wpos], src, cnt);
            _wpos += cnt;
        }

        void append(ByteBuffer const& buffer)
        {
            if(buffer.wpos())
                append(buffer.contents(), buffer.wpos());
        }

        void appendPackGUID(uint64 guid)
        {
            uint8 packGUID[8+1];
            packGUID[0] = 0;
            size_t size = 1;
            for (uint8 i = 0; guid != 0; ++i)
            {
                if (guid & 0xFF)
                {
                    packGUID[0] |= uint8(1 << i);
                    packGUID[size] =  uint8(guid & 0xFF);
                    ++size;
                }

                guid >>= 8;
            }

            append(packGUID, size);
        }

        void appendPackXYZ(float x, float y, float z)
        {
            uint32 packed = 0;
            packed |= ((int)(x / 0.25f) & 0x7FF);
            packed |= ((int)(y / 0.25f) & 0x7FF) << 11;
            packed |= ((int)(z / 0.25f) & 0x3FF) << 22;
            *this << packed;
        }

        void put(size_t pos, uint8 const* src, size_t cnt)
        {
            if(pos + cnt > size())
                throw ByteBufferException(true, pos, cnt, size());
            memcpy(&_storage[pos], src, cnt);
        }

        void print_storage() const
        {
            std::ostringstream ss;
            ss <<  "STORAGE_SIZE: " << size() << "\n";

            for (size_t i = 0; i < size(); ++i)
                ss << uint32(read<uint8>(i)) << " - ";

            printf(ss.str().c_str());
        }

        void textlike() const
        {
            std::ostringstream ss;
            ss <<  "STORAGE_SIZE: " << size() << "\n";

            for (size_t i = 0; i < size(); ++i)
                ss << read<uint8>(i);

            printf(ss.str().c_str());
        }

        void hexlike() const
        {
            std::ostringstream ss;
            ss <<  "STORAGE_SIZE: " << size() << "\n";

            size_t j = 1, k = 1;

            for (size_t i = 0; i < size(); ++i)
            {
                if ((i == (j * 8)) && ((i != (k * 16))))
                {
                    ss << "| ";
                    ++j;
                }
                else if (i == (k * 16))
                {
                    ss << "\n";

                    ++k;
                    ++j;
                }

                char buf[4];
                snprintf(buf, 4, "%02X", read<uint8>(i));
                ss << buf << " ";

            }
            printf(ss.str().c_str());
        }

    private:
        // limited for internal use because can "append" any unexpected type (like pointer and etc) with hard detection problem
        template <typename T> void append(T value)
        {
            #ifdef _WIN32
            EndianConvert(value);
            #endif
            append((uint8*)&value, sizeof(T));
        }

    protected:
        size_t _rpos, _wpos, _bitpos;
        uint8 _curbitval;
        std::vector<uint8> _storage;
};

template <typename T>
inline ByteBuffer& operator<<(ByteBuffer& b, std::vector<T> const& v)
{
    b << (uint32)v.size();
    for (typename std::vector<T>::iterator i = v.begin(); i != v.end(); ++i)
    {
        b << *i;
    }
    return b;
}

template <typename T>
inline ByteBuffer& operator>>(ByteBuffer& b, std::vector<T>& v)
{
    uint32 vsize;
    b >> vsize;
    v.clear();
    while(vsize--)
    {
        T t;
        b >> t;
        v.push_back(t);
    }
    return b;
}

template <typename T>
inline ByteBuffer& operator<<(ByteBuffer& b, std::list<T> const& v)
{
    b << (uint32)v.size();
    for (typename std::list<T>::iterator i = v.begin(); i != v.end(); ++i)
    {
        b << *i;
    }
    return b;
}

template <typename T>
inline ByteBuffer& operator>>(ByteBuffer& b, std::list<T>& v)
{
    uint32 vsize;
    b >> vsize;
    v.clear();
    while(vsize--)
    {
        T t;
        b >> t;
        v.push_back(t);
    }
    return b;
}

template <typename K, typename V>
inline ByteBuffer& operator<<(ByteBuffer& b, std::map<K, V>& m)
{
    b << (uint32)m.size();
    for (typename std::map<K, V>::iterator i = m.begin(); i != m.end(); ++i)
    {
        b << i->first << i->second;
    }
    return b;
}

template <typename K, typename V>
inline ByteBuffer& operator>>(ByteBuffer& b, std::map<K, V>& m)
{
    uint32 msize;
    b >> msize;
    m.clear();
    while(msize--)
    {
        K k;
        V v;
        b >> k >> v;
        m.insert(make_pair(k, v));
    }
    return b;
}

template<>
inline void ByteBuffer::read_skip<char*>()
{
    std::string temp;
    *this >> temp;
}

template<>
inline void ByteBuffer::read_skip<char const*>()
{
    read_skip<char*>();
}

template<>
inline void ByteBuffer::read_skip<std::string>()
{
    read_skip<char*>();
}
#endif
