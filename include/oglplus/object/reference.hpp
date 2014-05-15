/**
 *  @file oglplus/object/reference.hpp
 *  @brief Reference to an existing Object
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_OBJECT_REFERENCE_1405011014_HPP
#define OGLPLUS_OBJECT_REFERENCE_1405011014_HPP

#include <oglplus/fwd.hpp>
#include <oglplus/object/name.hpp>

namespace oglplus {

template <typename ObjTag>
struct AllowedSpecialization<Reference<ObjectName<ObjTag>>>
{ };

template <typename OpsTag, typename ObjTag>
struct AllowedSpecialization<Reference<ObjectOps<OpsTag, ObjTag>>>
{ };

/// Allows to make managed copies of instances of Object
/** For obvious reasons @ref oglplus_object "objects" are not copyable,
 *  only movable. There may however be situations where a temporary reference
 *  to the "master" object (with the knowledge that the original will
 *  be kept alive during the whole lifetime of the copy) is needed.
 *  The Reference template class allows to do such temporary references
 *  which have the same members and friend functions as the original
 *  object, and can be use in the same way, provided that the original
 *  instance is not destroyed before the managed copy.
 *
 *  Instances of Reference are may be for example created when accessing
 *  or iterating through the elements of an @ref oglplus::Sequence "Sequence".
 *
 *  @ingroup modifier_classes
 */
template <typename Object>
class Reference
 : public Object
 , public AllowedSpecialization<Reference<Object>>
{
public:
	Reference(ObjectName<typename ObjectTag<Object>::Type> object)
	{
		this->_copy(object);
	}
};

template <typename ObjTag>
class Reference<ObjectOps<tag::CurrentBound, ObjTag>>
 : public ObjectOps<tag::CurrentBound, ObjTag>
{
private:
	typedef ObjectOps<tag::CurrentBound, ObjTag> Base;
public:
	Reference(typename Base::Target init_tgt)
	{
		this->_copy(ObjBindingOps<ObjTag>::Binding(init_tgt));
		this->target = init_tgt;
	}
};

template <typename ObjectOps>
struct Reference<Object<ObjectOps>>
 : public Reference<ObjectOps>
{
public:
	Reference(ObjectName<typename ObjectTag<Object<ObjectOps>>::Type> object)
	 : Reference<ObjectOps>(object)
	{ }
};

} // namespace oglplus

#endif // include guard
