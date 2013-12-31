/*
 * MockSTREAM.h
 *
 *  Created on: 26.11.2013
 *      Author: damon
 */

#ifndef MOCKSTREAM_H_
#define MOCKSTREAM_H_

#include <gmock/gmock.h>

class MockSTREAM {
public:
  typedef void (*HandlerFun)();

  typedef enum {
    MemToPeripheral = 0,
    PeripheralToMem,
    MemToMem
  } Direction_e;

  MockSTREAM( )
      :
          _memBuff( 0 ),
          _periphBuff( 0 ) {
    ON_CALL(*this, SetMemoryAddr(::testing::_)).WillByDefault(
        ::testing::Invoke( this, &MockSTREAM::SetFromBuffAddr ) );
    ON_CALL(*this, SetPeripheralAddr(::testing::_)).WillByDefault(
        ::testing::Invoke( this, &MockSTREAM::SetOutBuffAddr ) );
    ON_CALL(*this, SetHandler(::testing::_)).WillByDefault(
        ::testing::Invoke( this, &MockSTREAM::SetHandlerAddr ) );
  }

  MOCK_METHOD0(Enable, void());
  MOCK_METHOD0(Disable, void());
  MOCK_METHOD0(isEnable, bool());
  MOCK_METHOD1(SetDir, void(Direction_e));
  MOCK_METHOD1(SetCircularMode, void(bool));
  MOCK_METHOD1(SetMemoryAddr, void(unsigned int *));
  MOCK_METHOD1(SetMemorySize, void(unsigned int));
  MOCK_METHOD1(MemoryIncrement, void(bool));
  MOCK_METHOD1(SetPeripheralAddr, void(unsigned int *));
  MOCK_METHOD1(SetPeripheralSize, void(unsigned int));
  MOCK_METHOD1(PeripheralIncrement, void(bool));

  MOCK_METHOD0(ClearHandler, void());
  MOCK_METHOD1(SetHandler, void(void (*)()));
  void Update() {
    _handler();
  }

  unsigned int *_memBuff;
  unsigned int *_periphBuff;
  void SetFromBuffAddr(unsigned int *addr) {
    _memBuff = addr;
  }
  void SetOutBuffAddr(unsigned int *addr) {
    _periphBuff = addr;
  }

  void SetHandlerAddr(HandlerFun handler) {
    _handler = handler;
  }

  HandlerFun _handler;
};

#endif /* MOCKSTREAM_H_ */
