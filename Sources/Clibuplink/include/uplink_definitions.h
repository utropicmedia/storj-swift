#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

typedef enum CipherSuite {
    STORJ_ENC_UNSPECIFIED = 0,
    STORJ_ENC_NULL        = 1,
    STORJ_ENC_AESGCM      = 2,
    STORJ_ENC_SECRET_BOX  = 3
} CipherSuite;

typedef enum RedundancyAlgorithm {
    STORJ_INVALID_REDUNDANCY_ALGORITHM = 0,
    STORJ_REED_SOLOMON                 = 1
} RedundancyAlgorithm;

typedef enum ListDirection {
    STORJ_BEFORE = -2,
    STORJ_BACKWARD = -1,
    STORJ_FORWARD = 1,
    STORJ_AFTER = 2
} ListDirection;

typedef struct APIKey           { long _handle; } APIKeyRef;
typedef struct Uplink           { long _handle; } UplinkRef;
typedef struct Project          { long _handle; } ProjectRef;
typedef struct Bucket           { long _handle; } BucketRef;
typedef struct Object           { long _handle; } ObjectRef;
typedef struct Downloader       { long _handle; } DownloaderRef;
typedef struct Uploader         { long _handle; } UploaderRef;
typedef struct EncryptionAccess { long _handle; } EncryptionAccessRef;
typedef struct Scope            { long _handle; } ScopeRef;

typedef struct UplinkConfig {
    struct {
        struct {
            bool skip_peer_ca_whitelist;
            char *peer_ca_whitelist_path;
        } tls;
        char *peer_id_version;
        int32_t max_inline_size;
        int32_t max_memory;
        int32_t dial_timeout;
        char *user_agent;
    } Volatile;
} UplinkConfig;

typedef struct EncryptionParameters {
    CipherSuite cipher_suite;
    int32_t     block_size;
} EncryptionParameters;

typedef struct RedundancyScheme {
    RedundancyAlgorithm algorithm;
    int32_t             share_size;
    int16_t             required_shares;
    int16_t             repair_shares;
    int16_t             optimal_shares;
    int16_t             total_shares;
} RedundancyScheme;

typedef struct BucketInfo {
    char                 *name;
    int64_t              created;
    CipherSuite          path_cipher;
    uint64_t             segment_size;
    EncryptionParameters encryption_parameters;
    RedundancyScheme     redundancy_scheme;
} BucketInfo;

typedef struct BucketConfig {
    CipherSuite          path_cipher;
    EncryptionParameters encryption_parameters;
    RedundancyScheme     redundancy_scheme;
} BucketConfig;

typedef struct BucketListOptions {
    char    *cursor;
    ListDirection  direction;
    int64_t limit;
} BucketListOptions;

typedef struct BucketList {
    bool       more;
    BucketInfo *items;
    int32_t    length;
} BucketList;

typedef struct ObjectInfo {
    uint32_t   version;
    BucketInfo bucket;
    char       *path;
    bool       is_prefix;
    char       *content_type;
    int64_t    size;
    int64_t    created;
    int64_t    modified;
    int64_t    expires;
} ObjectInfo;

typedef struct ObjectList {
    char       *bucket;
    char       *prefix;
    bool       more;
    ObjectInfo *items;
    int32_t    length;
} ObjectList;

typedef struct UploadOptions {
    char    *content_type;
    int64_t expires;
} UploadOptions;

typedef struct ListOptions {
    char           *prefix;
    char           *cursor;
    char           delimiter;
    bool           recursive;
    ListDirection  direction;
    int64_t        limit;
} ListOptions;

typedef struct ObjectMeta {
    char     *bucket;
    char     *path;
    bool     is_prefix;
    char     *content_type;
    int64_t  created;
    int64_t  modified;
    int64_t  expires;
    uint64_t size;
    uint8_t  *checksum_bytes;
    uint64_t checksum_length;
} ObjectMeta;

typedef struct EncryptionRestriction {
    char *bucket;
    char *path_prefix;
} EncryptionRestriction;

typedef struct Caveat { 
	bool disallow_reads;
	bool disallow_writes;
	bool disallow_lists;
	bool disallow_deletes;
} Caveat;