// Generated by the protocol buffer compiler.  DO NOT EDIT!
// NO CHECKED-IN PROTOBUF GENCODE
// source: message.proto
// Protobuf C++ Version: 5.29.1

#include "message.pb.h"

#include <algorithm>
#include <type_traits>
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/generated_message_tctable_impl.h"
#include "google/protobuf/extension_set.h"
#include "google/protobuf/generated_message_util.h"
#include "google/protobuf/wire_format_lite.h"
#include "google/protobuf/descriptor.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/reflection_ops.h"
#include "google/protobuf/wire_format.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"
PROTOBUF_PRAGMA_INIT_SEG
namespace _pb = ::google::protobuf;
namespace _pbi = ::google::protobuf::internal;
namespace _fl = ::google::protobuf::internal::field_layout;
namespace message {

inline constexpr GetVarifyResponse::Impl_::Impl_(
    ::_pbi::ConstantInitialized) noexcept
      : email_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        code_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        error_{0},
        _cached_size_{0} {}

template <typename>
PROTOBUF_CONSTEXPR GetVarifyResponse::GetVarifyResponse(::_pbi::ConstantInitialized)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::Message(_class_data_.base()),
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::Message(),
#endif  // PROTOBUF_CUSTOM_VTABLE
      _impl_(::_pbi::ConstantInitialized()) {
}
struct GetVarifyResponseDefaultTypeInternal {
  PROTOBUF_CONSTEXPR GetVarifyResponseDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~GetVarifyResponseDefaultTypeInternal() {}
  union {
    GetVarifyResponse _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 GetVarifyResponseDefaultTypeInternal _GetVarifyResponse_default_instance_;

inline constexpr GetVarifyRequest::Impl_::Impl_(
    ::_pbi::ConstantInitialized) noexcept
      : email_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        _cached_size_{0} {}

template <typename>
PROTOBUF_CONSTEXPR GetVarifyRequest::GetVarifyRequest(::_pbi::ConstantInitialized)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::Message(_class_data_.base()),
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::Message(),
#endif  // PROTOBUF_CUSTOM_VTABLE
      _impl_(::_pbi::ConstantInitialized()) {
}
struct GetVarifyRequestDefaultTypeInternal {
  PROTOBUF_CONSTEXPR GetVarifyRequestDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~GetVarifyRequestDefaultTypeInternal() {}
  union {
    GetVarifyRequest _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 GetVarifyRequestDefaultTypeInternal _GetVarifyRequest_default_instance_;
}  // namespace message
static constexpr const ::_pb::EnumDescriptor**
    file_level_enum_descriptors_message_2eproto = nullptr;
static constexpr const ::_pb::ServiceDescriptor**
    file_level_service_descriptors_message_2eproto = nullptr;
const ::uint32_t
    TableStruct_message_2eproto::offsets[] ABSL_ATTRIBUTE_SECTION_VARIABLE(
        protodesc_cold) = {
        ~0u,  // no _has_bits_
        PROTOBUF_FIELD_OFFSET(::message::GetVarifyRequest, _internal_metadata_),
        ~0u,  // no _extensions_
        ~0u,  // no _oneof_case_
        ~0u,  // no _weak_field_map_
        ~0u,  // no _inlined_string_donated_
        ~0u,  // no _split_
        ~0u,  // no sizeof(Split)
        PROTOBUF_FIELD_OFFSET(::message::GetVarifyRequest, _impl_.email_),
        ~0u,  // no _has_bits_
        PROTOBUF_FIELD_OFFSET(::message::GetVarifyResponse, _internal_metadata_),
        ~0u,  // no _extensions_
        ~0u,  // no _oneof_case_
        ~0u,  // no _weak_field_map_
        ~0u,  // no _inlined_string_donated_
        ~0u,  // no _split_
        ~0u,  // no sizeof(Split)
        PROTOBUF_FIELD_OFFSET(::message::GetVarifyResponse, _impl_.error_),
        PROTOBUF_FIELD_OFFSET(::message::GetVarifyResponse, _impl_.email_),
        PROTOBUF_FIELD_OFFSET(::message::GetVarifyResponse, _impl_.code_),
};

static const ::_pbi::MigrationSchema
    schemas[] ABSL_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
        {0, -1, -1, sizeof(::message::GetVarifyRequest)},
        {9, -1, -1, sizeof(::message::GetVarifyResponse)},
};
static const ::_pb::Message* const file_default_instances[] = {
    &::message::_GetVarifyRequest_default_instance_._instance,
    &::message::_GetVarifyResponse_default_instance_._instance,
};
const char descriptor_table_protodef_message_2eproto[] ABSL_ATTRIBUTE_SECTION_VARIABLE(
    protodesc_cold) = {
    "\n\rmessage.proto\022\007message\"!\n\020GetVarifyReq"
    "uest\022\r\n\005email\030\001 \001(\t\"\?\n\021GetVarifyResponse"
    "\022\r\n\005error\030\001 \001(\005\022\r\n\005email\030\002 \001(\t\022\014\n\004code\030\003"
    " \001(\t2W\n\rVarifyService\022F\n\rGetVarifyCode\022\031"
    ".message.GetVarifyRequest\032\032.message.GetV"
    "arifyResponseb\006proto3"
};
static ::absl::once_flag descriptor_table_message_2eproto_once;
PROTOBUF_CONSTINIT const ::_pbi::DescriptorTable descriptor_table_message_2eproto = {
    false,
    false,
    221,
    descriptor_table_protodef_message_2eproto,
    "message.proto",
    &descriptor_table_message_2eproto_once,
    nullptr,
    0,
    2,
    schemas,
    file_default_instances,
    TableStruct_message_2eproto::offsets,
    file_level_enum_descriptors_message_2eproto,
    file_level_service_descriptors_message_2eproto,
};
namespace message {
// ===================================================================

class GetVarifyRequest::_Internal {
 public:
};

GetVarifyRequest::GetVarifyRequest(::google::protobuf::Arena* arena)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::Message(arena, _class_data_.base()) {
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::Message(arena) {
#endif  // PROTOBUF_CUSTOM_VTABLE
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:message.GetVarifyRequest)
}
inline PROTOBUF_NDEBUG_INLINE GetVarifyRequest::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility, ::google::protobuf::Arena* arena,
    const Impl_& from, const ::message::GetVarifyRequest& from_msg)
      : email_(arena, from.email_),
        _cached_size_{0} {}

GetVarifyRequest::GetVarifyRequest(
    ::google::protobuf::Arena* arena,
    const GetVarifyRequest& from)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::Message(arena, _class_data_.base()) {
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::Message(arena) {
#endif  // PROTOBUF_CUSTOM_VTABLE
  GetVarifyRequest* const _this = this;
  (void)_this;
  _internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(
      from._internal_metadata_);
  new (&_impl_) Impl_(internal_visibility(), arena, from._impl_, from);

  // @@protoc_insertion_point(copy_constructor:message.GetVarifyRequest)
}
inline PROTOBUF_NDEBUG_INLINE GetVarifyRequest::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility,
    ::google::protobuf::Arena* arena)
      : email_(arena),
        _cached_size_{0} {}

inline void GetVarifyRequest::SharedCtor(::_pb::Arena* arena) {
  new (&_impl_) Impl_(internal_visibility(), arena);
}
GetVarifyRequest::~GetVarifyRequest() {
  // @@protoc_insertion_point(destructor:message.GetVarifyRequest)
  SharedDtor(*this);
}
inline void GetVarifyRequest::SharedDtor(MessageLite& self) {
  GetVarifyRequest& this_ = static_cast<GetVarifyRequest&>(self);
  this_._internal_metadata_.Delete<::google::protobuf::UnknownFieldSet>();
  ABSL_DCHECK(this_.GetArena() == nullptr);
  this_._impl_.email_.Destroy();
  this_._impl_.~Impl_();
}

inline void* GetVarifyRequest::PlacementNew_(const void*, void* mem,
                                        ::google::protobuf::Arena* arena) {
  return ::new (mem) GetVarifyRequest(arena);
}
constexpr auto GetVarifyRequest::InternalNewImpl_() {
  return ::google::protobuf::internal::MessageCreator::CopyInit(sizeof(GetVarifyRequest),
                                            alignof(GetVarifyRequest));
}
PROTOBUF_CONSTINIT
PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::google::protobuf::internal::ClassDataFull GetVarifyRequest::_class_data_ = {
    ::google::protobuf::internal::ClassData{
        &_GetVarifyRequest_default_instance_._instance,
        &_table_.header,
        nullptr,  // OnDemandRegisterArenaDtor
        nullptr,  // IsInitialized
        &GetVarifyRequest::MergeImpl,
        ::google::protobuf::Message::GetNewImpl<GetVarifyRequest>(),
#if defined(PROTOBUF_CUSTOM_VTABLE)
        &GetVarifyRequest::SharedDtor,
        ::google::protobuf::Message::GetClearImpl<GetVarifyRequest>(), &GetVarifyRequest::ByteSizeLong,
            &GetVarifyRequest::_InternalSerialize,
#endif  // PROTOBUF_CUSTOM_VTABLE
        PROTOBUF_FIELD_OFFSET(GetVarifyRequest, _impl_._cached_size_),
        false,
    },
    &GetVarifyRequest::kDescriptorMethods,
    &descriptor_table_message_2eproto,
    nullptr,  // tracker
};
const ::google::protobuf::internal::ClassData* GetVarifyRequest::GetClassData() const {
  ::google::protobuf::internal::PrefetchToLocalCache(&_class_data_);
  ::google::protobuf::internal::PrefetchToLocalCache(_class_data_.tc_table);
  return _class_data_.base();
}
PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<0, 1, 0, 38, 2> GetVarifyRequest::_table_ = {
  {
    0,  // no _has_bits_
    0, // no _extensions_
    1, 0,  // max_field_number, fast_idx_mask
    offsetof(decltype(_table_), field_lookup_table),
    4294967294,  // skipmap
    offsetof(decltype(_table_), field_entries),
    1,  // num_field_entries
    0,  // num_aux_entries
    offsetof(decltype(_table_), field_names),  // no aux_entries
    _class_data_.base(),
    nullptr,  // post_loop_handler
    ::_pbi::TcParser::GenericFallback,  // fallback
    #ifdef PROTOBUF_PREFETCH_PARSE_TABLE
    ::_pbi::TcParser::GetTable<::message::GetVarifyRequest>(),  // to_prefetch
    #endif  // PROTOBUF_PREFETCH_PARSE_TABLE
  }, {{
    // string email = 1;
    {::_pbi::TcParser::FastUS1,
     {10, 63, 0, PROTOBUF_FIELD_OFFSET(GetVarifyRequest, _impl_.email_)}},
  }}, {{
    65535, 65535
  }}, {{
    // string email = 1;
    {PROTOBUF_FIELD_OFFSET(GetVarifyRequest, _impl_.email_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kUtf8String | ::_fl::kRepAString)},
  }},
  // no aux_entries
  {{
    "\30\5\0\0\0\0\0\0"
    "message.GetVarifyRequest"
    "email"
  }},
};

PROTOBUF_NOINLINE void GetVarifyRequest::Clear() {
// @@protoc_insertion_point(message_clear_start:message.GetVarifyRequest)
  ::google::protobuf::internal::TSanWrite(&_impl_);
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.email_.ClearToEmpty();
  _internal_metadata_.Clear<::google::protobuf::UnknownFieldSet>();
}

#if defined(PROTOBUF_CUSTOM_VTABLE)
        ::uint8_t* GetVarifyRequest::_InternalSerialize(
            const MessageLite& base, ::uint8_t* target,
            ::google::protobuf::io::EpsCopyOutputStream* stream) {
          const GetVarifyRequest& this_ = static_cast<const GetVarifyRequest&>(base);
#else   // PROTOBUF_CUSTOM_VTABLE
        ::uint8_t* GetVarifyRequest::_InternalSerialize(
            ::uint8_t* target,
            ::google::protobuf::io::EpsCopyOutputStream* stream) const {
          const GetVarifyRequest& this_ = *this;
#endif  // PROTOBUF_CUSTOM_VTABLE
          // @@protoc_insertion_point(serialize_to_array_start:message.GetVarifyRequest)
          ::uint32_t cached_has_bits = 0;
          (void)cached_has_bits;

          // string email = 1;
          if (!this_._internal_email().empty()) {
            const std::string& _s = this_._internal_email();
            ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
                _s.data(), static_cast<int>(_s.length()), ::google::protobuf::internal::WireFormatLite::SERIALIZE, "message.GetVarifyRequest.email");
            target = stream->WriteStringMaybeAliased(1, _s, target);
          }

          if (PROTOBUF_PREDICT_FALSE(this_._internal_metadata_.have_unknown_fields())) {
            target =
                ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
                    this_._internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance), target, stream);
          }
          // @@protoc_insertion_point(serialize_to_array_end:message.GetVarifyRequest)
          return target;
        }

#if defined(PROTOBUF_CUSTOM_VTABLE)
        ::size_t GetVarifyRequest::ByteSizeLong(const MessageLite& base) {
          const GetVarifyRequest& this_ = static_cast<const GetVarifyRequest&>(base);
#else   // PROTOBUF_CUSTOM_VTABLE
        ::size_t GetVarifyRequest::ByteSizeLong() const {
          const GetVarifyRequest& this_ = *this;
#endif  // PROTOBUF_CUSTOM_VTABLE
          // @@protoc_insertion_point(message_byte_size_start:message.GetVarifyRequest)
          ::size_t total_size = 0;

          ::uint32_t cached_has_bits = 0;
          // Prevent compiler warnings about cached_has_bits being unused
          (void)cached_has_bits;

           {
            // string email = 1;
            if (!this_._internal_email().empty()) {
              total_size += 1 + ::google::protobuf::internal::WireFormatLite::StringSize(
                                              this_._internal_email());
            }
          }
          return this_.MaybeComputeUnknownFieldsSize(total_size,
                                                     &this_._impl_._cached_size_);
        }

void GetVarifyRequest::MergeImpl(::google::protobuf::MessageLite& to_msg, const ::google::protobuf::MessageLite& from_msg) {
  auto* const _this = static_cast<GetVarifyRequest*>(&to_msg);
  auto& from = static_cast<const GetVarifyRequest&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:message.GetVarifyRequest)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_email().empty()) {
    _this->_internal_set_email(from._internal_email());
  }
  _this->_internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(from._internal_metadata_);
}

void GetVarifyRequest::CopyFrom(const GetVarifyRequest& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:message.GetVarifyRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}


void GetVarifyRequest::InternalSwap(GetVarifyRequest* PROTOBUF_RESTRICT other) {
  using std::swap;
  auto* arena = GetArena();
  ABSL_DCHECK_EQ(arena, other->GetArena());
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.email_, &other->_impl_.email_, arena);
}

::google::protobuf::Metadata GetVarifyRequest::GetMetadata() const {
  return ::google::protobuf::Message::GetMetadataImpl(GetClassData()->full());
}
// ===================================================================

class GetVarifyResponse::_Internal {
 public:
};

GetVarifyResponse::GetVarifyResponse(::google::protobuf::Arena* arena)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::Message(arena, _class_data_.base()) {
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::Message(arena) {
#endif  // PROTOBUF_CUSTOM_VTABLE
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:message.GetVarifyResponse)
}
inline PROTOBUF_NDEBUG_INLINE GetVarifyResponse::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility, ::google::protobuf::Arena* arena,
    const Impl_& from, const ::message::GetVarifyResponse& from_msg)
      : email_(arena, from.email_),
        code_(arena, from.code_),
        _cached_size_{0} {}

GetVarifyResponse::GetVarifyResponse(
    ::google::protobuf::Arena* arena,
    const GetVarifyResponse& from)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::Message(arena, _class_data_.base()) {
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::Message(arena) {
#endif  // PROTOBUF_CUSTOM_VTABLE
  GetVarifyResponse* const _this = this;
  (void)_this;
  _internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(
      from._internal_metadata_);
  new (&_impl_) Impl_(internal_visibility(), arena, from._impl_, from);
  _impl_.error_ = from._impl_.error_;

  // @@protoc_insertion_point(copy_constructor:message.GetVarifyResponse)
}
inline PROTOBUF_NDEBUG_INLINE GetVarifyResponse::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility,
    ::google::protobuf::Arena* arena)
      : email_(arena),
        code_(arena),
        _cached_size_{0} {}

inline void GetVarifyResponse::SharedCtor(::_pb::Arena* arena) {
  new (&_impl_) Impl_(internal_visibility(), arena);
  _impl_.error_ = {};
}
GetVarifyResponse::~GetVarifyResponse() {
  // @@protoc_insertion_point(destructor:message.GetVarifyResponse)
  SharedDtor(*this);
}
inline void GetVarifyResponse::SharedDtor(MessageLite& self) {
  GetVarifyResponse& this_ = static_cast<GetVarifyResponse&>(self);
  this_._internal_metadata_.Delete<::google::protobuf::UnknownFieldSet>();
  ABSL_DCHECK(this_.GetArena() == nullptr);
  this_._impl_.email_.Destroy();
  this_._impl_.code_.Destroy();
  this_._impl_.~Impl_();
}

inline void* GetVarifyResponse::PlacementNew_(const void*, void* mem,
                                        ::google::protobuf::Arena* arena) {
  return ::new (mem) GetVarifyResponse(arena);
}
constexpr auto GetVarifyResponse::InternalNewImpl_() {
  return ::google::protobuf::internal::MessageCreator::CopyInit(sizeof(GetVarifyResponse),
                                            alignof(GetVarifyResponse));
}
PROTOBUF_CONSTINIT
PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::google::protobuf::internal::ClassDataFull GetVarifyResponse::_class_data_ = {
    ::google::protobuf::internal::ClassData{
        &_GetVarifyResponse_default_instance_._instance,
        &_table_.header,
        nullptr,  // OnDemandRegisterArenaDtor
        nullptr,  // IsInitialized
        &GetVarifyResponse::MergeImpl,
        ::google::protobuf::Message::GetNewImpl<GetVarifyResponse>(),
#if defined(PROTOBUF_CUSTOM_VTABLE)
        &GetVarifyResponse::SharedDtor,
        ::google::protobuf::Message::GetClearImpl<GetVarifyResponse>(), &GetVarifyResponse::ByteSizeLong,
            &GetVarifyResponse::_InternalSerialize,
#endif  // PROTOBUF_CUSTOM_VTABLE
        PROTOBUF_FIELD_OFFSET(GetVarifyResponse, _impl_._cached_size_),
        false,
    },
    &GetVarifyResponse::kDescriptorMethods,
    &descriptor_table_message_2eproto,
    nullptr,  // tracker
};
const ::google::protobuf::internal::ClassData* GetVarifyResponse::GetClassData() const {
  ::google::protobuf::internal::PrefetchToLocalCache(&_class_data_);
  ::google::protobuf::internal::PrefetchToLocalCache(_class_data_.tc_table);
  return _class_data_.base();
}
PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<2, 3, 0, 43, 2> GetVarifyResponse::_table_ = {
  {
    0,  // no _has_bits_
    0, // no _extensions_
    3, 24,  // max_field_number, fast_idx_mask
    offsetof(decltype(_table_), field_lookup_table),
    4294967288,  // skipmap
    offsetof(decltype(_table_), field_entries),
    3,  // num_field_entries
    0,  // num_aux_entries
    offsetof(decltype(_table_), field_names),  // no aux_entries
    _class_data_.base(),
    nullptr,  // post_loop_handler
    ::_pbi::TcParser::GenericFallback,  // fallback
    #ifdef PROTOBUF_PREFETCH_PARSE_TABLE
    ::_pbi::TcParser::GetTable<::message::GetVarifyResponse>(),  // to_prefetch
    #endif  // PROTOBUF_PREFETCH_PARSE_TABLE
  }, {{
    {::_pbi::TcParser::MiniParse, {}},
    // int32 error = 1;
    {::_pbi::TcParser::SingularVarintNoZag1<::uint32_t, offsetof(GetVarifyResponse, _impl_.error_), 63>(),
     {8, 63, 0, PROTOBUF_FIELD_OFFSET(GetVarifyResponse, _impl_.error_)}},
    // string email = 2;
    {::_pbi::TcParser::FastUS1,
     {18, 63, 0, PROTOBUF_FIELD_OFFSET(GetVarifyResponse, _impl_.email_)}},
    // string code = 3;
    {::_pbi::TcParser::FastUS1,
     {26, 63, 0, PROTOBUF_FIELD_OFFSET(GetVarifyResponse, _impl_.code_)}},
  }}, {{
    65535, 65535
  }}, {{
    // int32 error = 1;
    {PROTOBUF_FIELD_OFFSET(GetVarifyResponse, _impl_.error_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kInt32)},
    // string email = 2;
    {PROTOBUF_FIELD_OFFSET(GetVarifyResponse, _impl_.email_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kUtf8String | ::_fl::kRepAString)},
    // string code = 3;
    {PROTOBUF_FIELD_OFFSET(GetVarifyResponse, _impl_.code_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kUtf8String | ::_fl::kRepAString)},
  }},
  // no aux_entries
  {{
    "\31\0\5\4\0\0\0\0"
    "message.GetVarifyResponse"
    "email"
    "code"
  }},
};

PROTOBUF_NOINLINE void GetVarifyResponse::Clear() {
// @@protoc_insertion_point(message_clear_start:message.GetVarifyResponse)
  ::google::protobuf::internal::TSanWrite(&_impl_);
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.email_.ClearToEmpty();
  _impl_.code_.ClearToEmpty();
  _impl_.error_ = 0;
  _internal_metadata_.Clear<::google::protobuf::UnknownFieldSet>();
}

#if defined(PROTOBUF_CUSTOM_VTABLE)
        ::uint8_t* GetVarifyResponse::_InternalSerialize(
            const MessageLite& base, ::uint8_t* target,
            ::google::protobuf::io::EpsCopyOutputStream* stream) {
          const GetVarifyResponse& this_ = static_cast<const GetVarifyResponse&>(base);
#else   // PROTOBUF_CUSTOM_VTABLE
        ::uint8_t* GetVarifyResponse::_InternalSerialize(
            ::uint8_t* target,
            ::google::protobuf::io::EpsCopyOutputStream* stream) const {
          const GetVarifyResponse& this_ = *this;
#endif  // PROTOBUF_CUSTOM_VTABLE
          // @@protoc_insertion_point(serialize_to_array_start:message.GetVarifyResponse)
          ::uint32_t cached_has_bits = 0;
          (void)cached_has_bits;

          // int32 error = 1;
          if (this_._internal_error() != 0) {
            target = ::google::protobuf::internal::WireFormatLite::
                WriteInt32ToArrayWithField<1>(
                    stream, this_._internal_error(), target);
          }

          // string email = 2;
          if (!this_._internal_email().empty()) {
            const std::string& _s = this_._internal_email();
            ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
                _s.data(), static_cast<int>(_s.length()), ::google::protobuf::internal::WireFormatLite::SERIALIZE, "message.GetVarifyResponse.email");
            target = stream->WriteStringMaybeAliased(2, _s, target);
          }

          // string code = 3;
          if (!this_._internal_code().empty()) {
            const std::string& _s = this_._internal_code();
            ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
                _s.data(), static_cast<int>(_s.length()), ::google::protobuf::internal::WireFormatLite::SERIALIZE, "message.GetVarifyResponse.code");
            target = stream->WriteStringMaybeAliased(3, _s, target);
          }

          if (PROTOBUF_PREDICT_FALSE(this_._internal_metadata_.have_unknown_fields())) {
            target =
                ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
                    this_._internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance), target, stream);
          }
          // @@protoc_insertion_point(serialize_to_array_end:message.GetVarifyResponse)
          return target;
        }

#if defined(PROTOBUF_CUSTOM_VTABLE)
        ::size_t GetVarifyResponse::ByteSizeLong(const MessageLite& base) {
          const GetVarifyResponse& this_ = static_cast<const GetVarifyResponse&>(base);
#else   // PROTOBUF_CUSTOM_VTABLE
        ::size_t GetVarifyResponse::ByteSizeLong() const {
          const GetVarifyResponse& this_ = *this;
#endif  // PROTOBUF_CUSTOM_VTABLE
          // @@protoc_insertion_point(message_byte_size_start:message.GetVarifyResponse)
          ::size_t total_size = 0;

          ::uint32_t cached_has_bits = 0;
          // Prevent compiler warnings about cached_has_bits being unused
          (void)cached_has_bits;

          ::_pbi::Prefetch5LinesFrom7Lines(&this_);
           {
            // string email = 2;
            if (!this_._internal_email().empty()) {
              total_size += 1 + ::google::protobuf::internal::WireFormatLite::StringSize(
                                              this_._internal_email());
            }
            // string code = 3;
            if (!this_._internal_code().empty()) {
              total_size += 1 + ::google::protobuf::internal::WireFormatLite::StringSize(
                                              this_._internal_code());
            }
            // int32 error = 1;
            if (this_._internal_error() != 0) {
              total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(
                  this_._internal_error());
            }
          }
          return this_.MaybeComputeUnknownFieldsSize(total_size,
                                                     &this_._impl_._cached_size_);
        }

void GetVarifyResponse::MergeImpl(::google::protobuf::MessageLite& to_msg, const ::google::protobuf::MessageLite& from_msg) {
  auto* const _this = static_cast<GetVarifyResponse*>(&to_msg);
  auto& from = static_cast<const GetVarifyResponse&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:message.GetVarifyResponse)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_email().empty()) {
    _this->_internal_set_email(from._internal_email());
  }
  if (!from._internal_code().empty()) {
    _this->_internal_set_code(from._internal_code());
  }
  if (from._internal_error() != 0) {
    _this->_impl_.error_ = from._impl_.error_;
  }
  _this->_internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(from._internal_metadata_);
}

void GetVarifyResponse::CopyFrom(const GetVarifyResponse& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:message.GetVarifyResponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}


void GetVarifyResponse::InternalSwap(GetVarifyResponse* PROTOBUF_RESTRICT other) {
  using std::swap;
  auto* arena = GetArena();
  ABSL_DCHECK_EQ(arena, other->GetArena());
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.email_, &other->_impl_.email_, arena);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.code_, &other->_impl_.code_, arena);
        swap(_impl_.error_, other->_impl_.error_);
}

::google::protobuf::Metadata GetVarifyResponse::GetMetadata() const {
  return ::google::protobuf::Message::GetMetadataImpl(GetClassData()->full());
}
// @@protoc_insertion_point(namespace_scope)
}  // namespace message
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google
// @@protoc_insertion_point(global_scope)
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::std::false_type
    _static_init2_ PROTOBUF_UNUSED =
        (::_pbi::AddDescriptors(&descriptor_table_message_2eproto),
         ::std::false_type{});
#include "google/protobuf/port_undef.inc"