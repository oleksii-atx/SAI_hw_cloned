#include <stdio.h>
#include "sai.h"

const char* test_profile_get_value(
    _In_ sai_switch_profile_id_t profile_id,
    _In_ const char* variable)
{
    return 0;
}

int test_profile_get_next_value(
    _In_ sai_switch_profile_id_t profile_id,
    _Out_ const char** variable,
    _Out_ const char** value)
{
    return -1;
}

const service_method_table_t test_services = {
    test_profile_get_value,
    test_profile_get_next_value
};

int main()
{
    sai_status_t              status;
    sai_lag_api_t             *lag_api;
    sai_object_id_t           lag1_oid, lag2_oid;
    sai_object_id_t           lag_m1_oid, lag_m2_oid, lag_m3_oid, lag_m4_oid;
    sai_attribute_t           attrs[2];
    sai_object_id_t           port_list[64];

    status = sai_api_initialize(0, &test_services);
    if (status != SAI_STATUS_SUCCESS) {
        printf("SAI initialization failed, status=%d\n", status);
        return 1;
    }
    
    status = sai_api_query(SAI_API_LAG, (void**)&lag_api);
    if (status != SAI_STATUS_SUCCESS) {
        printf("LAG API query failed, status=%d\n", status);
        return 1;
    }

    //Create lag1
    status = lag_api->create_lag(&lag1_oid, 0, NULL);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Create LAG1 failed, status=%d\n", status);
        return 1;
    }

    //Create lag1 member1
    attrs[0].id = SAI_LAG_MEMBER_ATTR_LAG_ID;
    attrs[0].value.oid = lag1_oid;
    attrs[1].id = SAI_LAG_MEMBER_ATTR_PORT_ID;
    attrs[1].value.oid = 1;

    status = lag_api->create_lag_member(&lag_m1_oid, 2, attrs);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Create LAG1 member1 failed, status=%d\n", status);
        return 1;
    }

    //Create lag1 member2
    attrs[0].id = SAI_LAG_MEMBER_ATTR_LAG_ID;
    attrs[0].value.oid = lag1_oid;
    attrs[1].id = SAI_LAG_MEMBER_ATTR_PORT_ID;
    attrs[1].value.oid = 2;

    status = lag_api->create_lag_member(&lag_m2_oid, 2, attrs);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Create LAG1 member1 failed, status=%d\n", status);
        return 1;
    }

    //Create lag2
    status = lag_api->create_lag(&lag2_oid, 0, NULL);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Create LAG2 failed, status=%d\n", status);
        return 1;
    }

    //Create lag2 member1
    attrs[0].id = SAI_LAG_MEMBER_ATTR_LAG_ID;
    attrs[0].value.oid = lag2_oid;
    attrs[1].id = SAI_LAG_MEMBER_ATTR_PORT_ID;
    attrs[1].value.oid = 3;

    status = lag_api->create_lag_member(&lag_m3_oid, 2, attrs);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Create LAG2 member1 failed, status=%d\n", status);
        return 1;
    }

    //Create lag2 member2
    attrs[0].id = SAI_LAG_MEMBER_ATTR_LAG_ID;
    attrs[0].value.oid = lag2_oid;
    attrs[1].id = SAI_LAG_MEMBER_ATTR_PORT_ID;
    attrs[1].value.oid = 4;
    status = lag_api->create_lag_member(&lag_m4_oid, 2, attrs);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Create LAG2 member2 failed, status=%d\n", status);
        return 1;
    }

    //Get lag1 port list
    attrs[0].id = SAI_LAG_ATTR_PORT_LIST;
    attrs[0].value.objlist.count = 64;
    attrs[0].value.objlist.list = port_list;
    status = lag_api->get_lag_attribute(lag1_oid, 1, attrs);
    if (status != SAI_STATUS_SUCCESS && status != SAI_STATUS_NOT_IMPLEMENTED) {
        printf("Get LAG 1 port list failed, status=%d\n", status);
        return 1;
    }
    //skip for now
    /*else
    {
    	printf(" OK\n");
        for (int32_t i = 0; i < attrs[0].value.objlist.count; i++) {
            printf("    Port #%d OID: 0x%lX\n", i, attrs[0].value.objlist.list[i]);
        }
    }*/

    //Get lag2 port list
    attrs[0].id = SAI_LAG_ATTR_PORT_LIST;
    attrs[0].value.objlist.count = 64;
    attrs[0].value.objlist.list = port_list;
    status = lag_api->get_lag_attribute(lag2_oid, 1, attrs);
    if (status != SAI_STATUS_SUCCESS && status != SAI_STATUS_NOT_IMPLEMENTED) {
        printf("Get LAG 2 port list failed, status=%d\n", status);
        return 1;
    }

    //Get lag_m1 lag id
    attrs[0].id = SAI_LAG_MEMBER_ATTR_LAG_ID;
    status = lag_api->get_lag_member_attribute(lag_m1_oid, 1, attrs);
    if (status != SAI_STATUS_SUCCESS && status != SAI_STATUS_NOT_IMPLEMENTED) {
        printf("Get LAG member 1 lag id failed, status=%d\n", status);
        return 1;
    }

    //Get lag_m3 port id
    attrs[0].id = SAI_LAG_MEMBER_ATTR_PORT_ID;
    status = lag_api->get_lag_member_attribute(lag_m3_oid, 1, attrs);
    if (status != SAI_STATUS_SUCCESS && status != SAI_STATUS_NOT_IMPLEMENTED) {
        printf("Get LAG member 3 port id failed, status=%d\n", status);
        return 1;
    }

    //Remove lag_m2
    status = lag_api->remove_lag_member(lag_m2_oid);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Removing LAG member 2 failed, status=%d\n", status);
        return 1;
    }

    //Get lag1 port list
    attrs[0].id = SAI_LAG_ATTR_PORT_LIST;
    status = lag_api->get_lag_member_attribute(lag1_oid, 1, attrs);
    if (status != SAI_STATUS_SUCCESS && status != SAI_STATUS_NOT_IMPLEMENTED) {
        printf("Get LAG 1 port list failed, status=%d\n", status);
        return 1;
    }

    //Remove lag_m3
    status = lag_api->remove_lag_member(lag_m3_oid);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Removing LAG member 3 failed, status=%d\n", status);
        return 1;
    }

    //Get lag2 port list
    attrs[0].id = SAI_LAG_ATTR_PORT_LIST;
    status = lag_api->get_lag_member_attribute(lag2_oid, 1, attrs);
    if (status != SAI_STATUS_SUCCESS && status != SAI_STATUS_NOT_IMPLEMENTED) {
        printf("Get LAG 2 port list failed, status=%d\n", status);
        return 1;
    }

    //Remove lag_m1
    status = lag_api->remove_lag_member(lag_m1_oid);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Removing LAG member 1 failed, status=%d\n", status);
        return 1;
    }

    //Remove lag_m4
    status = lag_api->remove_lag_member(lag_m4_oid);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Removing LAG member 4 failed, status=%d\n", status);
        return 1;
    }

    //Remove lag1
    status = lag_api->remove_lag(lag1_oid);
    if (status != SAI_STATUS_SUCCESS && status != SAI_STATUS_NOT_IMPLEMENTED) {
        printf("LAG 1 removing failed, status=%d\n", status);
        return 1;
    }

    //Remove lag2
    status = lag_api->remove_lag(lag2_oid);
    if (status != SAI_STATUS_SUCCESS && status != SAI_STATUS_NOT_IMPLEMENTED) {
        printf("LAG 1 removing failed, status=%d\n", status);
        return 1;
    }

    status = sai_api_uninitialize();
    printf("SAI uninitialization");
    if (status != SAI_STATUS_SUCCESS) {
        printf(" failed, status=%d\n", status);
        return 1;
    }
    else {
        printf(" OK\n");
    }
    
    return 0;
}
