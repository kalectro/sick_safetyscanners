#pragma once

#include <sick_microscan3_ros_driver/datastructure/DataTypes.h>
#include <boost/type_traits/is_fundamental.hpp>

namespace sick {
namespace data_processing {

class ReadWriteHelper
{
public:
  ReadWriteHelper();

  /// Returns a value using Little Endian byte order from an memory buffer and increments the buffer afterwards
  static UINT8 readUINT8LE (const BYTE *&buf);


  /// Returns a value using Little Endian byte order from an memory buffer and increments the buffer afterwards
  static UINT16 readUINT16LE (const BYTE*& buf);


  /// Returns a value using Little Endian byte order from an memory buffer and increments the buffer afterwards
  static UINT32 readUINT32LE (const BYTE*& buf);

  /// Returns a value using Little Endian byte order from an memory buffer and increments the buffer afterwards
  static UINT64 readUINT64LE (const BYTE*& buf);

  static UINT8 readUINT8BE(const BYTE*& buf);
  static UINT16 readUINT16BE(const BYTE*& buf);
  static UINT32 readUINT32BE(const BYTE*& buf);
  static UINT64 readUINT64BE(const BYTE*& buf);
};

}
}
