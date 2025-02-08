#pragma once 

#include "utilities/Core.h"

namespace eb
{
	class Object : public std::enable_shared_from_this<Object>
	{
	public:
		Object();

		virtual void Destroy();
		bool IsPendingDestroy() const { return _isPendingDestroy; }

		weak_ptr<Object> GetWeakRef() { return weak_from_this(); }
		weak_ptr<const Object> GetWeakRef() const { return weak_from_this(); };

		~Object();

	private:
		bool _isPendingDestroy;
	};
}