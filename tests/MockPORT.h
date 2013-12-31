/*
 * MockPORT.h
 *
 *  Created on: 26.11.2013
 *      Author: damon
 */

#ifndef MOCKPORT_H_
#define MOCKPORT_H_

#include <gmock/gmock.h>

class MockPORT {
public:
  MOCK_METHOD0(GetInputDataReg, unsigned int *());
  MOCK_METHOD0(GetOutputDataReg, unsigned int *());
  MOCK_METHOD0(GetBitSetResetReg, unsigned int *());
};

#endif /* MOCKPORT_H_ */
