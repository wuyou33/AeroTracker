/* Software License Agreement (BSD License)
 *
 * Copyright (c) 2011, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 *  * Neither the name of Willow Garage, Inc. nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * Auto-generated by genmsg_cpp from file /home/pushyamikaveti/AeroTracker/src/core/msg/Camera_msgs.msg
 *
 */


#ifndef CORE_MESSAGE_CAMERA_MSGS_H
#define CORE_MESSAGE_CAMERA_MSGS_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace core
{
template <class ContainerAllocator>
struct Camera_msgs_
{
  typedef Camera_msgs_<ContainerAllocator> Type;

  Camera_msgs_()
    : center_x(0)
    , center_y(0)
    , centroid_x(0)
    , centroid_y(0)
    , time()  {
    }
  Camera_msgs_(const ContainerAllocator& _alloc)
    : center_x(0)
    , center_y(0)
    , centroid_x(0)
    , centroid_y(0)
    , time()  {
    }



   typedef int32_t _center_x_type;
  _center_x_type center_x;

   typedef int32_t _center_y_type;
  _center_y_type center_y;

   typedef int32_t _centroid_x_type;
  _centroid_x_type centroid_x;

   typedef int32_t _centroid_y_type;
  _centroid_y_type centroid_y;

   typedef ros::Time _time_type;
  _time_type time;




  typedef boost::shared_ptr< ::core::Camera_msgs_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::core::Camera_msgs_<ContainerAllocator> const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;

}; // struct Camera_msgs_

typedef ::core::Camera_msgs_<std::allocator<void> > Camera_msgs;

typedef boost::shared_ptr< ::core::Camera_msgs > Camera_msgsPtr;
typedef boost::shared_ptr< ::core::Camera_msgs const> Camera_msgsConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::core::Camera_msgs_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::core::Camera_msgs_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace core

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'core': ['/home/pushyamikaveti/AeroTracker/src/core/msg'], 'std_msgs': ['/opt/ros/hydro/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::core::Camera_msgs_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::core::Camera_msgs_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::core::Camera_msgs_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::core::Camera_msgs_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::core::Camera_msgs_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::core::Camera_msgs_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::core::Camera_msgs_<ContainerAllocator> >
{
  static const char* value()
  {
    return "8e94230b3f39704075111718d57a6c87";
  }

  static const char* value(const ::core::Camera_msgs_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x8e94230b3f397040ULL;
  static const uint64_t static_value2 = 0x75111718d57a6c87ULL;
};

template<class ContainerAllocator>
struct DataType< ::core::Camera_msgs_<ContainerAllocator> >
{
  static const char* value()
  {
    return "core/Camera_msgs";
  }

  static const char* value(const ::core::Camera_msgs_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::core::Camera_msgs_<ContainerAllocator> >
{
  static const char* value()
  {
    return "int32 center_x\n\
int32 center_y\n\
int32 centroid_x\n\
int32 centroid_y\n\
time time\n\
";
  }

  static const char* value(const ::core::Camera_msgs_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::core::Camera_msgs_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.center_x);
      stream.next(m.center_y);
      stream.next(m.centroid_x);
      stream.next(m.centroid_y);
      stream.next(m.time);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER;
  }; // struct Camera_msgs_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::core::Camera_msgs_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::core::Camera_msgs_<ContainerAllocator>& v)
  {
    s << indent << "center_x: ";
    Printer<int32_t>::stream(s, indent + "  ", v.center_x);
    s << indent << "center_y: ";
    Printer<int32_t>::stream(s, indent + "  ", v.center_y);
    s << indent << "centroid_x: ";
    Printer<int32_t>::stream(s, indent + "  ", v.centroid_x);
    s << indent << "centroid_y: ";
    Printer<int32_t>::stream(s, indent + "  ", v.centroid_y);
    s << indent << "time: ";
    Printer<ros::Time>::stream(s, indent + "  ", v.time);
  }
};

} // namespace message_operations
} // namespace ros

#endif // CORE_MESSAGE_CAMERA_MSGS_H