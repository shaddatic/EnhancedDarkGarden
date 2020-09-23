#pragma once
#include "SA2ModLoader.h"

static const void* const Transporter_LoadPtr = (void*)0x0057E4F0;
EntityData1* Transporter_Load(NJS_VECTOR* a1, int a2)
{
	EntityData1* result;
	__asm
	{
		push[a2]
		mov ebx, [a1]
		call Transporter_LoadPtr
		mov result, eax
	}
	return result;
}