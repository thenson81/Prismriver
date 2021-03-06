#pragma once

#include <winerror.h>

extern "C"
{
#include <libavutil/error.h>
}

using namespace System;

namespace Prismriver
{
	public ref class AVException sealed : public Exception
	{
	internal:
		AVException(String^ message) : Exception(message, nullptr) {}
		AVException(String^ message, Exception^ e) : Exception(message, e) {}

		AVException(HRESULT hr) : AVException(hr, nullptr) {}
		AVException(HRESULT hr, Exception^ e) :
			Exception(AVException::GetStringFromAVerror(hr), e)
		{
			this->HResult = hr;
		}

		static String^ GetStringFromAVerror(HRESULT hr)
		{
			char errbuf[AV_ERROR_MAX_STRING_SIZE];
			av_strerror(hr, reinterpret_cast<char*>(&errbuf), AV_ERROR_MAX_STRING_SIZE);
			return gcnew String(errbuf);
		}
	};
}
