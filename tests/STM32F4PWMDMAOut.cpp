/*
 * test_STM32F4DMADMA.cpp
 *
 *  Created on: 22.11.2013
 *      Author: damon
 */

#include <STM32F4/PWMDMAOut.h>
#include "MockSTREAM.h"
#include "MockPORT.h"

#include <algorithm>
#include <gtest/gtest.h>

using namespace std;
using ::testing::ElementsAreArray;
using ::testing::ElementsAre;
using ::testing::InSequence;
using ::testing::TypedEq;
using ::testing::DoubleEq;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::_;
using ::testing::A;

TEST(STM32F4DMAPortOut, Test5bit) {
  MockSTREAM stream;
  MockPORT port;
  const unsigned char len = 5;
  unsigned int var_array[ len ] = { };

  // Common param setup
  EXPECT_CALL(stream, SetDir(MockSTREAM::MemToPeripheral)).Times( 1 );
  EXPECT_CALL(stream, SetCircularMode(true)).Times( 1 );

  // Memmory param setup
  EXPECT_CALL(stream, SetMemoryAddr(_)).Times( 1 );
  EXPECT_CALL(stream, SetMemorySize(len)).Times( 1 );
  EXPECT_CALL(stream, MemoryIncrement(true)).Times( 1 );

  // Peripheral param setup
  EXPECT_CALL(port, GetBitSetResetReg()).Times( 1 );
  EXPECT_CALL(stream, SetPeripheralAddr(_)).Times( 1 );
  EXPECT_CALL(stream, SetPeripheralSize(1)).Times( 1 );
  EXPECT_CALL(stream, PeripheralIncrement(false)).Times( 1 );

  auto pwmDma = MakeSTM32F4DMAPortOut5Bit( stream, port );

  EXPECT_CALL(stream, Enable()).Times( 1 );
  pwmDma.Enable();
  ASSERT_THAT( var_array, ElementsAreArray(stream._memBuff, len) );

  var_array[ 0 ] = 0x00010000;
  var_array[ 1 ] = 0x00010000;
  var_array[ 2 ] = 0x00010000;
  var_array[ 3 ] = 0x00010000;
  var_array[ 4 ] = 0x00000001;
  auto pin0 = pwmDma.GetPin( 0 );
  pin0.SetPulseWidth( 1 );
  ASSERT_THAT( var_array, ElementsAreArray(stream._memBuff, len) );

  var_array[ 0 ] = 0x00090000;
  var_array[ 1 ] = 0x00010008;
  var_array[ 2 ] = 0x00090000;
  var_array[ 3 ] = 0x00090000;
  var_array[ 4 ] = 0x00080001;
  auto pin3 = pwmDma.GetPin( 3 );
  pin3.SetPulseWidth( 8 );
  ASSERT_THAT( var_array, ElementsAreArray(stream._memBuff, len) );

  var_array[ 0 ] = 0x00090080;
  var_array[ 1 ] = 0x00010088;
  var_array[ 2 ] = 0x00890000;
  var_array[ 3 ] = 0x00090080;
  var_array[ 4 ] = 0x00880001;
  auto pin7 = pwmDma.GetPin( 7 );
  pin7.SetPulseWidth( 0x1A );
  ASSERT_THAT( var_array, ElementsAreArray(stream._memBuff, len) );

  var_array[ 0 ] = 0x00890000;
  var_array[ 1 ] = 0x00810008;
  var_array[ 2 ] = 0x00890000;
  var_array[ 3 ] = 0x00890000;
  var_array[ 4 ] = 0x00880001;
  pin7.Clear( );
  ASSERT_THAT( var_array, ElementsAreArray(stream._memBuff, len) );

  var_array[ 0 ] = 0x00890000;
  var_array[ 1 ] = 0x00890000;
  var_array[ 2 ] = 0x00890000;
  var_array[ 3 ] = 0x00890000;
  var_array[ 4 ] = 0x00880001;
  pin3.Clear( );
  ASSERT_THAT( var_array, ElementsAreArray(stream._memBuff, len) );

  var_array[ 0 ] = 0x00890000;
  var_array[ 1 ] = 0x00890000;
  var_array[ 2 ] = 0x00890000;
  var_array[ 3 ] = 0x00890000;
  var_array[ 4 ] = 0x00890000;
  pin0.Clear( );
  ASSERT_THAT( var_array, ElementsAreArray(stream._memBuff, len) );

  var_array[ 0 ] = 0x00890000;
  var_array[ 1 ] = 0x00890000;
  var_array[ 2 ] = 0x00890000;
  var_array[ 3 ] = 0x00890000;
  var_array[ 4 ] = 0x00880001;
  pin0.SetPulseWidth( 1 );
  ASSERT_THAT( var_array, ElementsAreArray(stream._memBuff, len) );

  var_array[ 0 ] = 0x00890000;
  var_array[ 1 ] = 0x00810008;
  var_array[ 2 ] = 0x00890000;
  var_array[ 3 ] = 0x00890000;
  var_array[ 4 ] = 0x00880001;
  pin3.SetPulseWidth( 8 );
  ASSERT_THAT( var_array, ElementsAreArray(stream._memBuff, len) );

  var_array[ 0 ] = 0x00090080;
  var_array[ 1 ] = 0x00010088;
  var_array[ 2 ] = 0x00890000;
  var_array[ 3 ] = 0x00090080;
  var_array[ 4 ] = 0x00880001;
  pin7.SetPulseWidth( 0x1A );
  ASSERT_THAT( var_array, ElementsAreArray(stream._memBuff, len) );
}

TEST(STM32F4DMAPortOut, Test8bit) {
  MockSTREAM stream;
  MockPORT port;
  const unsigned char len = 8;
  unsigned int var_array[ len ] = { };

  // Common param setup
  EXPECT_CALL(stream, SetDir(MockSTREAM::MemToPeripheral)).Times( 1 );
  EXPECT_CALL(stream, SetCircularMode(true)).Times( 1 );

  // Memmory param setup
  EXPECT_CALL(stream, SetMemoryAddr(_)).Times( 1 );
  EXPECT_CALL(stream, SetMemorySize(len)).Times( 1 );
  EXPECT_CALL(stream, MemoryIncrement(true)).Times( 1 );

  // Peripheral param setup
  EXPECT_CALL(port, GetBitSetResetReg()).Times( 1 );
  EXPECT_CALL(stream, SetPeripheralAddr(_)).Times( 1 );
  EXPECT_CALL(stream, SetPeripheralSize(1)).Times( 1 );
  EXPECT_CALL(stream, PeripheralIncrement(false)).Times( 1 );

  auto pwmDma = MakeSTM32F4DMAPortOut8Bit( stream, port );

  EXPECT_CALL(stream, Enable()).Times( 1 );
  pwmDma.Enable();
  ASSERT_THAT( var_array, ElementsAreArray(stream._memBuff, len) );

  var_array[ 0 ] = 0x00010000;
  var_array[ 1 ] = 0x00010000;
  var_array[ 2 ] = 0x00010000;
  var_array[ 3 ] = 0x00010000;
  var_array[ 4 ] = 0x00010000;
  var_array[ 5 ] = 0x00010000;
  var_array[ 6 ] = 0x00010000;
  var_array[ 7 ] = 0x00000001;
  auto pin0 = pwmDma.GetPin( 0 );
  pin0.SetPulseWidth( 1 );
  ASSERT_THAT( var_array, ElementsAreArray(stream._memBuff, len) );

  var_array[ 0 ] = 0x00090000;
  var_array[ 1 ] = 0x00090000;
  var_array[ 2 ] = 0x00090000;
  var_array[ 3 ] = 0x00090000;
  var_array[ 4 ] = 0x00010008;
  var_array[ 5 ] = 0x00090000;
  var_array[ 6 ] = 0x00090000;
  var_array[ 7 ] = 0x00080001;
  auto pin3 = pwmDma.GetPin( 3 );
  pin3.SetPulseWidth( 8 );
  ASSERT_THAT( var_array, ElementsAreArray(stream._memBuff, len) );

  var_array[ 0 ] = 0x00090080;
  var_array[ 1 ] = 0x00890000;
  var_array[ 2 ] = 0x00090080;
  var_array[ 3 ] = 0x00890000;
  var_array[ 4 ] = 0x00010088;
  var_array[ 5 ] = 0x00890000;
  var_array[ 6 ] = 0x00090080;
  var_array[ 7 ] = 0x00880001;
  auto pin7 = pwmDma.GetPin( 7 );
  pin7.SetPulseWidth( 0xAA );
  ASSERT_THAT( var_array, ElementsAreArray(stream._memBuff, len) );
}

TEST(STM32F4DMAPortOut, Test12bit) {
  MockSTREAM stream;
  MockPORT port;
  const unsigned char len = 12;
  unsigned int var_array[ len ] = { };

  // Common param setup
  EXPECT_CALL(stream, SetDir(MockSTREAM::MemToPeripheral)).Times( 1 );
  EXPECT_CALL(stream, SetCircularMode(true)).Times( 1 );

  // Memmory param setup
  EXPECT_CALL(stream, SetMemoryAddr(_)).Times( 1 );
  EXPECT_CALL(stream, SetMemorySize(len)).Times( 1 );
  EXPECT_CALL(stream, MemoryIncrement(true)).Times( 1 );

  // Peripheral param setup
  EXPECT_CALL(port, GetBitSetResetReg()).Times( 1 );
  EXPECT_CALL(stream, SetPeripheralAddr(_)).Times( 1 );
  EXPECT_CALL(stream, SetPeripheralSize(1)).Times( 1 );
  EXPECT_CALL(stream, PeripheralIncrement(false)).Times( 1 );

  auto pwmDma = MakeSTM32F4DMAPortOut12Bit( stream, port );

  EXPECT_CALL(stream, Enable()).Times( 1 );
  pwmDma.Enable();
  ASSERT_THAT( var_array, ElementsAreArray(stream._memBuff, len) );

  var_array[ 0 ] = 0x00010000;
  var_array[ 1 ] = 0x00010000;
  var_array[ 2 ] = 0x00010000;
  var_array[ 3 ] = 0x00010000;
  var_array[ 4 ] = 0x00010000;
  var_array[ 5 ] = 0x00010000;
  var_array[ 6 ] = 0x00010000;
  var_array[ 7 ] = 0x00010000;
  var_array[ 8 ] = 0x00010000;
  var_array[ 9 ] = 0x00010000;
  var_array[ 10 ] = 0x00010000;
  var_array[ 11 ] = 0x00000001;
  auto pin0 = pwmDma.GetPin( 0 );
  pin0.SetPulseWidth( 1 );
  ASSERT_THAT( var_array, ElementsAreArray(stream._memBuff, len) );

  var_array[ 0 ] = 0x00090000;
  var_array[ 1 ] = 0x00090000;
  var_array[ 2 ] = 0x00090000;
  var_array[ 3 ] = 0x00090000;
  var_array[ 4 ] = 0x00090000;
  var_array[ 5 ] = 0x00090000;
  var_array[ 6 ] = 0x00090000;
  var_array[ 7 ] = 0x00090000;
  var_array[ 8 ] = 0x00010008;
  var_array[ 9 ] = 0x00090000;
  var_array[ 10 ] = 0x00090000;
  var_array[ 11 ] = 0x00080001;
  auto pin3 = pwmDma.GetPin( 3 );
  pin3.SetPulseWidth( 8 );
  ASSERT_THAT( var_array, ElementsAreArray(stream._memBuff, len) );

  var_array[ 0 ] = 0x00090080;
  var_array[ 1 ] = 0x00890000;
  var_array[ 2 ] = 0x00090080;
  var_array[ 3 ] = 0x00890000;
  var_array[ 4 ] = 0x00090080;
  var_array[ 5 ] = 0x00890000;
  var_array[ 6 ] = 0x00090080;
  var_array[ 7 ] = 0x00890000;
  var_array[ 8 ] = 0x00010088;
  var_array[ 9 ] = 0x00890000;
  var_array[ 10 ] = 0x00090080;
  var_array[ 11 ] = 0x00880001;
  auto pin7 = pwmDma.GetPin( 7 );
  pin7.SetPulseWidth( 0xAAA );
  ASSERT_THAT( var_array, ElementsAreArray(stream._memBuff, len) );
}
