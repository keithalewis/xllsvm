// addin.h - convenience wrapper for Excel add-ins
// Copyright (c) KALX, LLC. All rights reserved. No warranty made.
#pragma once
#include "auto.h"
#include "args.h"

namespace xll {
	/// Manage the lifecycle of an Excel add-in.
	class AddIn {
	public:
		/// Register and Unregister an add-in when Excel calls xlAutoOpen and xlAutoClose.
		AddIn(const Args& args)
		{
			Auto<Open> ao([args]() { 
				return args.Register().isNum();
			});
			Auto<Close> ac([args]() {
				return args.Unregister();
			});
		}
	};
	using AddIn12 = AddIn;
	using AddInX = AddIn;
} // xll namespace


