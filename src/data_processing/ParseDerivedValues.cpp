#include <sick_microscan3_ros_driver/data_processing/ParseDerivedValues.h>

namespace sick {
namespace data_processing {

ParseDerivedValues::ParseDerivedValues()
{
  m_reader_ptr = boost::make_shared<sick::data_processing::ReadWriteHelper>();

}

datastructure::DerivedValues ParseDerivedValues::parseUDPSequence(datastructure::PacketBuffer buffer, datastructure::Data &data)
{
  datastructure::DerivedValues derived_values;


  if (!checkIfPreconditionsAreMet(data)) {
    derived_values.setIsEmpty(true);
    return derived_values;
  }
  const BYTE* data_ptr(buffer.getBuffer().data() + data.getDataHeaderPtr()->getDerivedValuesBlockOffset());
  setDataInDerivedValues(data_ptr, derived_values);
  return derived_values;
}

bool ParseDerivedValues::checkIfPreconditionsAreMet(datastructure::Data &data)
{
  if (!checkIfDerivedValuesIsPublished(data))
  {
    return false;
  }
  if (!checkIfDataContainsNeededParsedBlocks(data))
  {
    return false;
  }

  return true;

}

bool ParseDerivedValues::checkIfDerivedValuesIsPublished(datastructure::Data &data)
{
  if (data.getDataHeaderPtr()->getDerivedValuesBlockOffset() == 0 && data.getDataHeaderPtr()->getDerivedValuesBlockSize() == 0)
  {
    return false;
  }
  return true;

}

bool ParseDerivedValues::checkIfDataContainsNeededParsedBlocks(datastructure::Data &data)
{
  if (data.getDataHeaderPtr()->isEmpty()){
    return false;
  }
  return true;

}

bool ParseDerivedValues::setDataInDerivedValues(const BYTE* data_ptr, datastructure::DerivedValues &derived_values)
{
  setMultiplicationFactorInDerivedValues(data_ptr, derived_values);
  setNumberOfBeamsInDerivedValues(data_ptr, derived_values);
  setScanTimeInDerivedValues(data_ptr, derived_values);
  setStartAngleInDerivedValues(data_ptr, derived_values);
  setAngularBeamResolutionInDerivedValues(data_ptr, derived_values);
  setInterbeamPeriodInDerivedValues(data_ptr, derived_values);
}

bool ParseDerivedValues::setMultiplicationFactorInDerivedValues(const BYTE* data_ptr, datastructure::DerivedValues &derived_values)
{
  derived_values.setMultiplicationFactor(m_reader_ptr->readUINT16LittleEndian(data_ptr, 0));
}

bool ParseDerivedValues::setNumberOfBeamsInDerivedValues(const BYTE* data_ptr, datastructure::DerivedValues &derived_values)
{
  derived_values.setNumberOfBeams(m_reader_ptr->readUINT16LittleEndian(data_ptr, 2));
}

bool ParseDerivedValues::setScanTimeInDerivedValues(const BYTE* data_ptr, datastructure::DerivedValues &derived_values)
{
  derived_values.setScanTime(m_reader_ptr->readUINT16LittleEndian(data_ptr, 4));
}

bool ParseDerivedValues::setStartAngleInDerivedValues(const BYTE* data_ptr, datastructure::DerivedValues &derived_values)
{
  derived_values.setStartAngle(m_reader_ptr->readINT32LittleEndian(data_ptr, 8));
}

bool ParseDerivedValues::setAngularBeamResolutionInDerivedValues(const BYTE* data_ptr, datastructure::DerivedValues &derived_values)
{
  derived_values.setAngularBeamResolution(m_reader_ptr->readINT32LittleEndian(data_ptr, 12) );
}

bool ParseDerivedValues::setInterbeamPeriodInDerivedValues(const BYTE* data_ptr, datastructure::DerivedValues &derived_values)
{
  derived_values.setInterbeamPeriod(m_reader_ptr->readUINT32LittleEndian(data_ptr, 16));
}

}
}

