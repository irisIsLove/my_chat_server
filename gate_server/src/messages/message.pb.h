// Generated by the protocol buffer compiler.  DO NOT EDIT!
// NO CHECKED-IN PROTOBUF GENCODE
// source: message.proto
// Protobuf C++ Version: 5.29.1

#ifndef message_2eproto_2epb_2eh
#define message_2eproto_2epb_2eh

#include <limits>
#include <string>
#include <type_traits>
#include <utility>

#include "google/protobuf/runtime_version.h"
#if PROTOBUF_VERSION != 5029001
#error "Protobuf C++ gencode is built with an incompatible version of"
#error "Protobuf C++ headers/runtime. See"
#error "https://protobuf.dev/support/cross-version-runtime-guarantee/#cpp"
#endif
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/arena.h"
#include "google/protobuf/arenastring.h"
#include "google/protobuf/generated_message_tctable_decl.h"
#include "google/protobuf/generated_message_util.h"
#include "google/protobuf/metadata_lite.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/message.h"
#include "google/protobuf/message_lite.h"
#include "google/protobuf/repeated_field.h"  // IWYU pragma: export
#include "google/protobuf/extension_set.h"  // IWYU pragma: export
#include "google/protobuf/unknown_field_set.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"

#define PROTOBUF_INTERNAL_EXPORT_message_2eproto

namespace google {
namespace protobuf {
namespace internal {
template <typename T>
::absl::string_view GetAnyMessageName();
}  // namespace internal
}  // namespace protobuf
}  // namespace google

// Internal implementation detail -- do not use these members.
struct TableStruct_message_2eproto {
  static const ::uint32_t offsets[];
};
extern const ::google::protobuf::internal::DescriptorTable
    descriptor_table_message_2eproto;
namespace message {
class GetVarifyRequest;
struct GetVarifyRequestDefaultTypeInternal;
extern GetVarifyRequestDefaultTypeInternal _GetVarifyRequest_default_instance_;
class GetVarifyResponse;
struct GetVarifyResponseDefaultTypeInternal;
extern GetVarifyResponseDefaultTypeInternal _GetVarifyResponse_default_instance_;
}  // namespace message
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google

namespace message {

// ===================================================================


// -------------------------------------------------------------------

class GetVarifyResponse final
    : public ::google::protobuf::Message
/* @@protoc_insertion_point(class_definition:message.GetVarifyResponse) */ {
 public:
  inline GetVarifyResponse() : GetVarifyResponse(nullptr) {}
  ~GetVarifyResponse() PROTOBUF_FINAL;

#if defined(PROTOBUF_CUSTOM_VTABLE)
  void operator delete(GetVarifyResponse* msg, std::destroying_delete_t) {
    SharedDtor(*msg);
    ::google::protobuf::internal::SizedDelete(msg, sizeof(GetVarifyResponse));
  }
#endif

  template <typename = void>
  explicit PROTOBUF_CONSTEXPR GetVarifyResponse(
      ::google::protobuf::internal::ConstantInitialized);

  inline GetVarifyResponse(const GetVarifyResponse& from) : GetVarifyResponse(nullptr, from) {}
  inline GetVarifyResponse(GetVarifyResponse&& from) noexcept
      : GetVarifyResponse(nullptr, std::move(from)) {}
  inline GetVarifyResponse& operator=(const GetVarifyResponse& from) {
    CopyFrom(from);
    return *this;
  }
  inline GetVarifyResponse& operator=(GetVarifyResponse&& from) noexcept {
    if (this == &from) return *this;
    if (::google::protobuf::internal::CanMoveWithInternalSwap(GetArena(), from.GetArena())) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance);
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields()
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.mutable_unknown_fields<::google::protobuf::UnknownFieldSet>();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::google::protobuf::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::google::protobuf::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const GetVarifyResponse& default_instance() {
    return *internal_default_instance();
  }
  static inline const GetVarifyResponse* internal_default_instance() {
    return reinterpret_cast<const GetVarifyResponse*>(
        &_GetVarifyResponse_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 1;
  friend void swap(GetVarifyResponse& a, GetVarifyResponse& b) { a.Swap(&b); }
  inline void Swap(GetVarifyResponse* other) {
    if (other == this) return;
    if (::google::protobuf::internal::CanUseInternalSwap(GetArena(), other->GetArena())) {
      InternalSwap(other);
    } else {
      ::google::protobuf::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(GetVarifyResponse* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  GetVarifyResponse* New(::google::protobuf::Arena* arena = nullptr) const {
    return ::google::protobuf::Message::DefaultConstruct<GetVarifyResponse>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const GetVarifyResponse& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom(const GetVarifyResponse& from) { GetVarifyResponse::MergeImpl(*this, from); }

  private:
  static void MergeImpl(
      ::google::protobuf::MessageLite& to_msg,
      const ::google::protobuf::MessageLite& from_msg);

  public:
  bool IsInitialized() const {
    return true;
  }
  ABSL_ATTRIBUTE_REINITIALIZES void Clear() PROTOBUF_FINAL;
  #if defined(PROTOBUF_CUSTOM_VTABLE)
  private:
  static ::size_t ByteSizeLong(const ::google::protobuf::MessageLite& msg);
  static ::uint8_t* _InternalSerialize(
      const MessageLite& msg, ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream);

  public:
  ::size_t ByteSizeLong() const { return ByteSizeLong(*this); }
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream) const {
    return _InternalSerialize(*this, target, stream);
  }
  #else   // PROTOBUF_CUSTOM_VTABLE
  ::size_t ByteSizeLong() const final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream) const final;
  #endif  // PROTOBUF_CUSTOM_VTABLE
  int GetCachedSize() const { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::google::protobuf::Arena* arena);
  static void SharedDtor(MessageLite& self);
  void InternalSwap(GetVarifyResponse* other);
 private:
  template <typename T>
  friend ::absl::string_view(
      ::google::protobuf::internal::GetAnyMessageName)();
  static ::absl::string_view FullMessageName() { return "message.GetVarifyResponse"; }

 protected:
  explicit GetVarifyResponse(::google::protobuf::Arena* arena);
  GetVarifyResponse(::google::protobuf::Arena* arena, const GetVarifyResponse& from);
  GetVarifyResponse(::google::protobuf::Arena* arena, GetVarifyResponse&& from) noexcept
      : GetVarifyResponse(arena) {
    *this = ::std::move(from);
  }
  const ::google::protobuf::internal::ClassData* GetClassData() const PROTOBUF_FINAL;
  static void* PlacementNew_(const void*, void* mem,
                             ::google::protobuf::Arena* arena);
  static constexpr auto InternalNewImpl_();
  static const ::google::protobuf::internal::ClassDataFull _class_data_;

 public:
  ::google::protobuf::Metadata GetMetadata() const;
  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------
  enum : int {
    kEmailFieldNumber = 2,
    kCodeFieldNumber = 3,
    kErrorFieldNumber = 1,
  };
  // string email = 2;
  void clear_email() ;
  const std::string& email() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_email(Arg_&& arg, Args_... args);
  std::string* mutable_email();
  PROTOBUF_NODISCARD std::string* release_email();
  void set_allocated_email(std::string* value);

  private:
  const std::string& _internal_email() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_email(
      const std::string& value);
  std::string* _internal_mutable_email();

  public:
  // string code = 3;
  void clear_code() ;
  const std::string& code() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_code(Arg_&& arg, Args_... args);
  std::string* mutable_code();
  PROTOBUF_NODISCARD std::string* release_code();
  void set_allocated_code(std::string* value);

  private:
  const std::string& _internal_code() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_code(
      const std::string& value);
  std::string* _internal_mutable_code();

  public:
  // int32 error = 1;
  void clear_error() ;
  ::int32_t error() const;
  void set_error(::int32_t value);

  private:
  ::int32_t _internal_error() const;
  void _internal_set_error(::int32_t value);

  public:
  // @@protoc_insertion_point(class_scope:message.GetVarifyResponse)
 private:
  class _Internal;
  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      2, 3, 0,
      43, 2>
      _table_;

  friend class ::google::protobuf::MessageLite;
  friend class ::google::protobuf::Arena;
  template <typename T>
  friend class ::google::protobuf::Arena::InternalHelper;
  using InternalArenaConstructable_ = void;
  using DestructorSkippable_ = void;
  struct Impl_ {
    inline explicit constexpr Impl_(
        ::google::protobuf::internal::ConstantInitialized) noexcept;
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena);
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena, const Impl_& from,
                          const GetVarifyResponse& from_msg);
    ::google::protobuf::internal::ArenaStringPtr email_;
    ::google::protobuf::internal::ArenaStringPtr code_;
    ::int32_t error_;
    ::google::protobuf::internal::CachedSize _cached_size_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_message_2eproto;
};
// -------------------------------------------------------------------

class GetVarifyRequest final
    : public ::google::protobuf::Message
/* @@protoc_insertion_point(class_definition:message.GetVarifyRequest) */ {
 public:
  inline GetVarifyRequest() : GetVarifyRequest(nullptr) {}
  ~GetVarifyRequest() PROTOBUF_FINAL;

#if defined(PROTOBUF_CUSTOM_VTABLE)
  void operator delete(GetVarifyRequest* msg, std::destroying_delete_t) {
    SharedDtor(*msg);
    ::google::protobuf::internal::SizedDelete(msg, sizeof(GetVarifyRequest));
  }
#endif

  template <typename = void>
  explicit PROTOBUF_CONSTEXPR GetVarifyRequest(
      ::google::protobuf::internal::ConstantInitialized);

  inline GetVarifyRequest(const GetVarifyRequest& from) : GetVarifyRequest(nullptr, from) {}
  inline GetVarifyRequest(GetVarifyRequest&& from) noexcept
      : GetVarifyRequest(nullptr, std::move(from)) {}
  inline GetVarifyRequest& operator=(const GetVarifyRequest& from) {
    CopyFrom(from);
    return *this;
  }
  inline GetVarifyRequest& operator=(GetVarifyRequest&& from) noexcept {
    if (this == &from) return *this;
    if (::google::protobuf::internal::CanMoveWithInternalSwap(GetArena(), from.GetArena())) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance);
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields()
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.mutable_unknown_fields<::google::protobuf::UnknownFieldSet>();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::google::protobuf::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::google::protobuf::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const GetVarifyRequest& default_instance() {
    return *internal_default_instance();
  }
  static inline const GetVarifyRequest* internal_default_instance() {
    return reinterpret_cast<const GetVarifyRequest*>(
        &_GetVarifyRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 0;
  friend void swap(GetVarifyRequest& a, GetVarifyRequest& b) { a.Swap(&b); }
  inline void Swap(GetVarifyRequest* other) {
    if (other == this) return;
    if (::google::protobuf::internal::CanUseInternalSwap(GetArena(), other->GetArena())) {
      InternalSwap(other);
    } else {
      ::google::protobuf::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(GetVarifyRequest* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  GetVarifyRequest* New(::google::protobuf::Arena* arena = nullptr) const {
    return ::google::protobuf::Message::DefaultConstruct<GetVarifyRequest>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const GetVarifyRequest& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom(const GetVarifyRequest& from) { GetVarifyRequest::MergeImpl(*this, from); }

  private:
  static void MergeImpl(
      ::google::protobuf::MessageLite& to_msg,
      const ::google::protobuf::MessageLite& from_msg);

  public:
  bool IsInitialized() const {
    return true;
  }
  ABSL_ATTRIBUTE_REINITIALIZES void Clear() PROTOBUF_FINAL;
  #if defined(PROTOBUF_CUSTOM_VTABLE)
  private:
  static ::size_t ByteSizeLong(const ::google::protobuf::MessageLite& msg);
  static ::uint8_t* _InternalSerialize(
      const MessageLite& msg, ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream);

  public:
  ::size_t ByteSizeLong() const { return ByteSizeLong(*this); }
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream) const {
    return _InternalSerialize(*this, target, stream);
  }
  #else   // PROTOBUF_CUSTOM_VTABLE
  ::size_t ByteSizeLong() const final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream) const final;
  #endif  // PROTOBUF_CUSTOM_VTABLE
  int GetCachedSize() const { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::google::protobuf::Arena* arena);
  static void SharedDtor(MessageLite& self);
  void InternalSwap(GetVarifyRequest* other);
 private:
  template <typename T>
  friend ::absl::string_view(
      ::google::protobuf::internal::GetAnyMessageName)();
  static ::absl::string_view FullMessageName() { return "message.GetVarifyRequest"; }

 protected:
  explicit GetVarifyRequest(::google::protobuf::Arena* arena);
  GetVarifyRequest(::google::protobuf::Arena* arena, const GetVarifyRequest& from);
  GetVarifyRequest(::google::protobuf::Arena* arena, GetVarifyRequest&& from) noexcept
      : GetVarifyRequest(arena) {
    *this = ::std::move(from);
  }
  const ::google::protobuf::internal::ClassData* GetClassData() const PROTOBUF_FINAL;
  static void* PlacementNew_(const void*, void* mem,
                             ::google::protobuf::Arena* arena);
  static constexpr auto InternalNewImpl_();
  static const ::google::protobuf::internal::ClassDataFull _class_data_;

 public:
  ::google::protobuf::Metadata GetMetadata() const;
  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------
  enum : int {
    kEmailFieldNumber = 1,
  };
  // string email = 1;
  void clear_email() ;
  const std::string& email() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_email(Arg_&& arg, Args_... args);
  std::string* mutable_email();
  PROTOBUF_NODISCARD std::string* release_email();
  void set_allocated_email(std::string* value);

  private:
  const std::string& _internal_email() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_email(
      const std::string& value);
  std::string* _internal_mutable_email();

  public:
  // @@protoc_insertion_point(class_scope:message.GetVarifyRequest)
 private:
  class _Internal;
  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      0, 1, 0,
      38, 2>
      _table_;

  friend class ::google::protobuf::MessageLite;
  friend class ::google::protobuf::Arena;
  template <typename T>
  friend class ::google::protobuf::Arena::InternalHelper;
  using InternalArenaConstructable_ = void;
  using DestructorSkippable_ = void;
  struct Impl_ {
    inline explicit constexpr Impl_(
        ::google::protobuf::internal::ConstantInitialized) noexcept;
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena);
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena, const Impl_& from,
                          const GetVarifyRequest& from_msg);
    ::google::protobuf::internal::ArenaStringPtr email_;
    ::google::protobuf::internal::CachedSize _cached_size_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_message_2eproto;
};

// ===================================================================




// ===================================================================


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// GetVarifyRequest

// string email = 1;
inline void GetVarifyRequest::clear_email() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.email_.ClearToEmpty();
}
inline const std::string& GetVarifyRequest::email() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:message.GetVarifyRequest.email)
  return _internal_email();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void GetVarifyRequest::set_email(Arg_&& arg,
                                                     Args_... args) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.email_.Set(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:message.GetVarifyRequest.email)
}
inline std::string* GetVarifyRequest::mutable_email() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_email();
  // @@protoc_insertion_point(field_mutable:message.GetVarifyRequest.email)
  return _s;
}
inline const std::string& GetVarifyRequest::_internal_email() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.email_.Get();
}
inline void GetVarifyRequest::_internal_set_email(const std::string& value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.email_.Set(value, GetArena());
}
inline std::string* GetVarifyRequest::_internal_mutable_email() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  return _impl_.email_.Mutable( GetArena());
}
inline std::string* GetVarifyRequest::release_email() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  // @@protoc_insertion_point(field_release:message.GetVarifyRequest.email)
  return _impl_.email_.Release();
}
inline void GetVarifyRequest::set_allocated_email(std::string* value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.email_.SetAllocated(value, GetArena());
  if (::google::protobuf::internal::DebugHardenForceCopyDefaultString() && _impl_.email_.IsDefault()) {
    _impl_.email_.Set("", GetArena());
  }
  // @@protoc_insertion_point(field_set_allocated:message.GetVarifyRequest.email)
}

// -------------------------------------------------------------------

// GetVarifyResponse

// int32 error = 1;
inline void GetVarifyResponse::clear_error() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.error_ = 0;
}
inline ::int32_t GetVarifyResponse::error() const {
  // @@protoc_insertion_point(field_get:message.GetVarifyResponse.error)
  return _internal_error();
}
inline void GetVarifyResponse::set_error(::int32_t value) {
  _internal_set_error(value);
  // @@protoc_insertion_point(field_set:message.GetVarifyResponse.error)
}
inline ::int32_t GetVarifyResponse::_internal_error() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.error_;
}
inline void GetVarifyResponse::_internal_set_error(::int32_t value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.error_ = value;
}

// string email = 2;
inline void GetVarifyResponse::clear_email() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.email_.ClearToEmpty();
}
inline const std::string& GetVarifyResponse::email() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:message.GetVarifyResponse.email)
  return _internal_email();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void GetVarifyResponse::set_email(Arg_&& arg,
                                                     Args_... args) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.email_.Set(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:message.GetVarifyResponse.email)
}
inline std::string* GetVarifyResponse::mutable_email() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_email();
  // @@protoc_insertion_point(field_mutable:message.GetVarifyResponse.email)
  return _s;
}
inline const std::string& GetVarifyResponse::_internal_email() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.email_.Get();
}
inline void GetVarifyResponse::_internal_set_email(const std::string& value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.email_.Set(value, GetArena());
}
inline std::string* GetVarifyResponse::_internal_mutable_email() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  return _impl_.email_.Mutable( GetArena());
}
inline std::string* GetVarifyResponse::release_email() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  // @@protoc_insertion_point(field_release:message.GetVarifyResponse.email)
  return _impl_.email_.Release();
}
inline void GetVarifyResponse::set_allocated_email(std::string* value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.email_.SetAllocated(value, GetArena());
  if (::google::protobuf::internal::DebugHardenForceCopyDefaultString() && _impl_.email_.IsDefault()) {
    _impl_.email_.Set("", GetArena());
  }
  // @@protoc_insertion_point(field_set_allocated:message.GetVarifyResponse.email)
}

// string code = 3;
inline void GetVarifyResponse::clear_code() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.code_.ClearToEmpty();
}
inline const std::string& GetVarifyResponse::code() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:message.GetVarifyResponse.code)
  return _internal_code();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void GetVarifyResponse::set_code(Arg_&& arg,
                                                     Args_... args) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.code_.Set(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:message.GetVarifyResponse.code)
}
inline std::string* GetVarifyResponse::mutable_code() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_code();
  // @@protoc_insertion_point(field_mutable:message.GetVarifyResponse.code)
  return _s;
}
inline const std::string& GetVarifyResponse::_internal_code() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.code_.Get();
}
inline void GetVarifyResponse::_internal_set_code(const std::string& value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.code_.Set(value, GetArena());
}
inline std::string* GetVarifyResponse::_internal_mutable_code() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  return _impl_.code_.Mutable( GetArena());
}
inline std::string* GetVarifyResponse::release_code() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  // @@protoc_insertion_point(field_release:message.GetVarifyResponse.code)
  return _impl_.code_.Release();
}
inline void GetVarifyResponse::set_allocated_code(std::string* value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.code_.SetAllocated(value, GetArena());
  if (::google::protobuf::internal::DebugHardenForceCopyDefaultString() && _impl_.code_.IsDefault()) {
    _impl_.code_.Set("", GetArena());
  }
  // @@protoc_insertion_point(field_set_allocated:message.GetVarifyResponse.code)
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)
}  // namespace message


// @@protoc_insertion_point(global_scope)

#include "google/protobuf/port_undef.inc"

#endif  // message_2eproto_2epb_2eh
