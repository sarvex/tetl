/*
Copyright (c) 2019-2020, Tobias Hienzsch
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
DAMAGE.
*/

#ifndef TAETL_RTOS_STUBS_HPP
#define TAETL_RTOS_STUBS_HPP

#include "taetl/warning.hpp"

// TASK
struct tskTaskControlBlock;

using TaskHandle_t           = tskTaskControlBlock*;
using TaskFunction_t         = void (*)(void*);
using BaseType_t             = long;
using UBaseType_t            = unsigned long;
using configSTACK_DEPTH_TYPE = taetl::uint16_t;

inline auto xTaskCreate(TaskFunction_t pvTaskCode, const char* const pcName,
                        configSTACK_DEPTH_TYPE usStackDepth,
                        void* const pvParameters, UBaseType_t uxPriority,
                        TaskHandle_t* const pxCreatedTask) -> BaseType_t
{
    taetl::ignore_unused(pvTaskCode, pcName, usStackDepth, pvParameters,
                         uxPriority, pxCreatedTask);
    return 0;
}

inline auto vTaskStartScheduler() -> void { }

// QUEUE
struct QueueDefinition;
using QueueHandle_t = QueueDefinition*;

inline auto xQueueCreate(UBaseType_t uxQueueLength, UBaseType_t uxItemSize)
    -> QueueHandle_t
{
    taetl::ignore_unused(uxQueueLength, uxItemSize);
    return nullptr;
}

auto vQueueDelete(QueueHandle_t xQueue) -> void
{
    taetl::ignore_unused(xQueue);
}

#endif  // TAETL_RTOS_STUBS_HPP