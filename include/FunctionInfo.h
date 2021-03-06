/**
 * Copyright (c) 2014, Michael Pekar
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef _include_functioninfo_h_
#define _include_functioninfo_h_

#include "DetourDecon.h"

/**
 * @brief Enumerates supported calling conventions.
 */
typedef enum CallConvention
{
    CallConv_cdecl = 0,
    CallConv_stdcall,
    //CallConv_fastcall,
    CallConv_thiscall    /**< not supported yet. */
} callConv_e;

/**
 * @brief Lists available parameter types.
 */
typedef enum ParameterType
{
    ParamType_POD,        /**< Plain old data. */
    ParamType_ByRef,    /**< Pass by reference. */
    ParamType_Float,    /**< Floating point. */
} paramType_e;

typedef struct Parameter
{
    paramType_e type;
    int size;
} param_t;

typedef struct FuncProto
{
    callConv_e callconv;
    int paramCount;
    param_t *params;
    param_t ret;
} prototype_t;

template<int P_COUNT>
class TPrototype
{
    param_t paraminf_[P_COUNT];
    prototype_t proto_;
    int idx_;
public:
    TPrototype(callConv_e x):
      idx_(0)
    {
        proto_.callconv = x;
        proto_.paramCount = P_COUNT;
        proto_.params = paraminf_;
        proto_.ret.size = 0;
    }
    void AddParam(int sz, paramType_e type)
    {
        paraminf_[idx_].size = sz;
        paraminf_[idx_++].type = type;
    }
    void SetReturn(int sz, paramType_e type)
    {
        proto_.ret.size = sz;
        proto_.ret.type = type;
    }
    void SetReturnNone()
    {
        proto_.ret.size = 0;
    }
    prototype_t *Prototype()
    {
        return proto_;
    }
};

#endif //_include_functioninfo_h_
