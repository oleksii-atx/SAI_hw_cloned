#include "sai.h"
#include "stub_sai.h"
#include "assert.h"

char * lag_attr_to_str( sai_attr_id_t type ){
	switch(type)
	{
		case SAI_LAG_ATTR_PORT_LIST:
			return "SAI_LAG_ATTR_PORT_LIST";
		default:
			return "NA";
	}
}

char * lag_member_attr_to_str( sai_attr_id_t type ){
	switch(type)
	{
		case SAI_LAG_MEMBER_ATTR_LAG_ID:
			return "SAI_LAG_MEMBER_ATTR_LAG_ID";
		case SAI_LAG_MEMBER_ATTR_PORT_ID:
			return "SAI_LAG_MEMBER_ATTR_PORT_ID";
		default:
			return "NA";
	}
}

sai_status_t stub_create_lag(
    _Out_ sai_object_id_t* lag_id,
    _In_ uint32_t attr_count,
    _In_ sai_attribute_t *attr_list)
{
	static int32_t next_lag_id = 1;
	sai_status_t status;
	status = stub_create_object(SAI_OBJECT_TYPE_LAG, next_lag_id++, lag_id);
	if (status != SAI_STATUS_SUCCESS) {
	    printf("Cannot create a LAG OID\n");
	}
	else{
		printf("CREATE LAG: 0x%lX\n", *lag_id);
	}
    return status;
}

sai_status_t stub_remove_lag(
    _In_ sai_object_id_t  lag_id)
{
	printf("REMOVE LAG: 0x%lX\n", lag_id);
    return SAI_STATUS_SUCCESS;
}

sai_status_t stub_set_lag_attribute(
    _In_ sai_object_id_t  lag_id,
    _In_ const sai_attribute_t *attr)
{
	printf("UPDATE LAG: 0x%lX\n", lag_id);
    return SAI_STATUS_NOT_IMPLEMENTED;
}

sai_status_t stub_get_lag_attribute(
    _In_ sai_object_id_t lag_id,
    _In_ uint32_t attr_count,
    _Inout_ sai_attribute_t *attr_list)
{
	for(uint32_t i = 0; i < attr_count; ++i )
	{
		printf("GET LAG 0x%lX %s \n", lag_id, lag_attr_to_str(attr_list[i].id));
	}
    return SAI_STATUS_NOT_IMPLEMENTED;
}

sai_status_t stub_create_lag_member(
    _Out_ sai_object_id_t* lag_member_id,
    _In_ uint32_t attr_count,
    _In_ sai_attribute_t *attr_list)
{
	static int32_t next_lag_member_id = 1;
	sai_status_t status;
	status = stub_create_object(SAI_OBJECT_TYPE_LAG_MEMBER, next_lag_member_id++, lag_member_id);
	if (status != SAI_STATUS_SUCCESS) {
	    printf("Cannot create a LAG member OID\n");
	}
	else
	{
		if( attr_count != 2 ){
			printf("Cannot create a LAG member, wrong attributes count\n");
			return SAI_STATUS_FAILURE;
		}
		sai_object_id_t *lag_oid = NULL;
		sai_object_id_t *port_oid = NULL;
		for (uint32_t i = 0; i < attr_count; ++i){
			switch (attr_list[i].id){
				case SAI_LAG_MEMBER_ATTR_LAG_ID:
					lag_oid = &attr_list[i].value.oid;
					break;
				case SAI_LAG_MEMBER_ATTR_PORT_ID:
					port_oid = &attr_list[i].value.oid;
					break;
			}
		}
		if (lag_oid == NULL || port_oid == NULL)
		{
			printf ("Cannot create a LAG member, parameter missed\n");
			return SAI_STATUS_INVALID_PARAMETER;
		}
		printf ("CREATE LAG MEMBER: 0x%lX {LAG 0x%lX PORT 0x%lX}\n", *lag_member_id, *lag_oid, *port_oid);
	}
    return status;
}

sai_status_t stub_remove_lag_member(
    _In_ sai_object_id_t  lag_member_id)
{
	printf ("REMOVE LAG MEMBER: 0x%lX\n", lag_member_id);
    return SAI_STATUS_SUCCESS;
}

sai_status_t stub_set_lag_member_attribute(
    _In_ sai_object_id_t  lag_member_id,
    _In_ const sai_attribute_t *attr)
{
	printf("UPDATE LAG MEMBER: 0x%lX\n", lag_member_id);
    return SAI_STATUS_NOT_IMPLEMENTED;
}

sai_status_t stub_get_lag_member_attribute(
    _In_ sai_object_id_t lag_member_id,
    _In_ uint32_t attr_count,
    _Inout_ sai_attribute_t *attr_list)
{
	for(uint32_t i = 0; i < attr_count; ++i )
	{
		printf("GET LAG MEMBER 0x%lX %s \n", lag_member_id, lag_member_attr_to_str(attr_list[i].id));
	}
    return SAI_STATUS_NOT_IMPLEMENTED;
}

const sai_lag_api_t lag_api = {
    stub_create_lag,
    stub_remove_lag,
    stub_set_lag_attribute,
    stub_get_lag_attribute,
    stub_create_lag_member,
    stub_remove_lag_member,
    stub_set_lag_member_attribute,
    stub_get_lag_member_attribute
};
