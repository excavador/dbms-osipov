#include "error.h"
#include "metadata.h"

Metadata* metadata_create(const DBC config)
{
    Metadata* result;

    result = (Metadata*) page_create(config.chunk_size, cPageMetadata);

    if (NULL == result)
        return NULL;

    result->db_size    = config.db_size;
    result->page_size  = config.chunk_size;
    result->page_root  = cPageInvalid;
    result->page_index = cPageInvalid;

    return result;
}


Metadata* metadata_parse(void* raw)
{
    Metadata* result;

    result = (Metadata*) page_parse(raw, 0);

    if (cPageMetadata != result->common.kind)
    {
        error_code = ERROR_PAGE_UNEXPECTED_KIND;
        return NULL;
    }

    return result;
}
