/*  =========================================================================
    asset_msg - assets management protocol
    
    Codec header for asset_msg.

    ** WARNING *************************************************************
    THIS SOURCE FILE IS 100% GENERATED. If you edit this file, you will lose
    your changes at the next build cycle. This is great for temporary printf
    statements. DO NOT MAKE ANY CHANGES YOU WISH TO KEEP. The correct places
    for commits are:

     * The XML model used for this code generation: asset_msg.xml, or
     * The code generation script that built this file: zproto_codec_c_v1
    ************************************************************************
                                                                        
    Copyright (C) 2014 Eaton                                            
                                                                        
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or   
    (at your option) any later version.                                 
                                                                        
    This program is distributed in the hope that it will be useful,     
    but WITHOUT ANY WARRANTY; without even the implied warranty of      
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the       
    GNU General Public License for more details.                        
                                                                        
    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
    =========================================================================
*/

#ifndef __ASSET_MSG_H_INCLUDED__
#define __ASSET_MSG_H_INCLUDED__

/*  These are the asset_msg messages:

    ELEMENT - Structure describing an asset element.
        name                string      Name of the element
        location            number 4    ID of the parent element
        location_type       number 1    Type of the parent element, defined in asset_type
        type                number 1    Type of the element, defined in asset_type
        ext                 hash        Hash map of extended attributes

    DEVICE - Structure describing an asset device.
        device_type         string      Type of the device from t_bios_asset_device_type
        groups              strings     List of IDs of groups device belongs to
        powers              strings     List of strings in form src_socket:src_id:dst_socket:dst_id
        ip                  string      IP of the device
        hostname            string      Hostname
        fqdn                string      Fully qualified domain name
        mac                 string      MAC address of the device
        msg                 msg         Element that we are extending to the device

    GET_ELEMENT - Ask for a specific element.
        element_id          number 4    Unique ID of the asset element
        type                number 1    Type of the element defined in asset_type (includes devices)

    RETURN_ELEMENT - Returns sn element we were asked for.
        element_id          number 4    Unique ID of the asset element
        msg                 msg         Element (or device) to be delivered

    UPDATE_ELEMENT - Updates an element.
        element_id          number 4    Unique ID of the asset element
        msg                 msg         Element (or device) to be updated

    INSERT_ELEMENT - Inserts an element.
        msg                 msg         Element (or device) message to be inserted

    DELETE_ELEMENT - Deletes an element.
        element_id          number 4    Unique ID of the element to be deleted
        type                number 1    Type of the element, defined in asset_type

    OK - Message from database that everything was processed successfully.
        element_id          number 4    Unique ID of the element that was proccessed

    FAIL - Message from database that something went wrong.
        error_id            number 1    Type of the error, enum defined in persistence header file

    GET_ELEMENTS - Ask for all elements of specific type.
        type                number 1    Type of the element, defined in asset_type

    RETURN_ELEMENTS - Returns elements we were asked for.
        element_ids         hash        Unique IDs of the asset element (as a key) mapped to the elements name (as a value)

    GET_LOCATION_FROM - Ask for location topology starting from the specified element.
        element_id          number 4    Unique ID of the start asset element
        recursive           number 1    If the search should be recursive (=1) or not (=0)
        filter_type         number 1    Type of the looked elements, if 7 take all

    GET_LOCATION_TO - Ask for a location topology for the specified element.
        element_id          number 4    Unique ID of the asset element

    RETURN_LOCATION_TO - Reply for a location topology for the specified element.
        element_id          number 4    Unique ID of the asset element
        type                number 1    Type of the element
        name                string      Name of the asset element
        type_name           string      Type of the device (or group), string from t_bios_asset_device_type (t_bios_asset_ext_attributes), if it is not a divece nor a group, then it is an empty string
        msg                 msg          parent of the element, this msg

    RETURN_LOCATION_FROM - Reply for the ask for a location topology for the specified element.
        element_id          number 4    Unique ID of the asset element
        type                number 1    Type of the element
        name                string      Name of the asset element
        type_name           string      Type of the device (or group), string from t_bios_asset_device_type (t_bios_asset_ext_attributes), if it is not a divece nor a group, then it is an empty string
        dcs                 frame       List of datacenters, matryoshka of this msg
        rooms               frame       List of rooms, matryoshka of this msg
        rows                frame       List of rows, matryoshka of this msg
        racks               frame       List of racks, matryoshka of this msg
        devices             frame       List of devices, matryoshka of this msg
        grps                frame       List of groups, matryoshka of this msg

    GET_POWER_FROM - Request for a list of devices directly powered from the specified device.
        element_id          number 4    Unique asset element ID of the device

    POWERCHAIN_DEVICE - Structure briefly describing the device contained in powerchain.
        element_id          number 4    Unique asset element ID of the device
        type_name           string      Type of the device
        name                string      Asset element name of the device

    RETURN_POWER - Reply for any power topology request.
        devices             frame       List of devices(id, name, typename), matroyska of he powerchain_device
        powers              strings     List of strings in form "src_socket:src_id:dst_socket:dst_id"

    GET_POWER_TO - Request for a full power chain which powers the requested target device.
        element_id          number 4    Unique asset element ID of the device

    GET_POWER_GROUP - Request for a full power chain from the group.
        element_id          number 4    Unique asset element ID of the group

    GET_POWER_DATACENTER - Request for a full power chains in the target datacenter.
        element_id          number 4    Unique asset element ID of the datacenter
*/

#define ASSET_MSG_VERSION                   1.0

#define ASSET_MSG_ELEMENT                   1
#define ASSET_MSG_DEVICE                    2
#define ASSET_MSG_GET_ELEMENT               3
#define ASSET_MSG_RETURN_ELEMENT            4
#define ASSET_MSG_UPDATE_ELEMENT            5
#define ASSET_MSG_INSERT_ELEMENT            6
#define ASSET_MSG_DELETE_ELEMENT            7
#define ASSET_MSG_OK                        8
#define ASSET_MSG_FAIL                      9
#define ASSET_MSG_GET_ELEMENTS              10
#define ASSET_MSG_RETURN_ELEMENTS           11
#define ASSET_MSG_GET_LOCATION_FROM         12
#define ASSET_MSG_GET_LOCATION_TO           13
#define ASSET_MSG_RETURN_LOCATION_TO        14
#define ASSET_MSG_RETURN_LOCATION_FROM      15
#define ASSET_MSG_GET_POWER_FROM            16
#define ASSET_MSG_POWERCHAIN_DEVICE         17
#define ASSET_MSG_RETURN_POWER              18
#define ASSET_MSG_GET_POWER_TO              19
#define ASSET_MSG_GET_POWER_GROUP           20
#define ASSET_MSG_GET_POWER_DATACENTER      21

#include <czmq.h>

#ifdef __cplusplus
extern "C" {
#endif

//  Opaque class structure
#ifndef ASSET_MSG_T_DEFINED
typedef struct _asset_msg_t asset_msg_t;
#define ASSET_MSG_T_DEFINED
#endif

//  @interface
//  Create a new asset_msg
asset_msg_t *
    asset_msg_new (int id);

//  Destroy the asset_msg
void
    asset_msg_destroy (asset_msg_t **self_p);

//  Parse a zmsg_t and decides whether it is asset_msg. Returns
//  true if it is, false otherwise. Doesn't destroy or modify the
//  original message.
bool
    is_asset_msg (zmsg_t *msg_p);

//  Parse a asset_msg from zmsg_t. Returns a new object, or NULL if
//  the message could not be parsed, or was NULL. Destroys msg and 
//  nullifies the msg reference.
asset_msg_t *
    asset_msg_decode (zmsg_t **msg_p);

//  Encode asset_msg into zmsg and destroy it. Returns a newly created
//  object or NULL if error. Use when not in control of sending the message.
zmsg_t *
    asset_msg_encode (asset_msg_t **self_p);

//  Receive and parse a asset_msg from the socket. Returns new object, 
//  or NULL if error. Will block if there's no message waiting.
asset_msg_t *
    asset_msg_recv (void *input);

//  Receive and parse a asset_msg from the socket. Returns new object, 
//  or NULL either if there was no input waiting, or the recv was interrupted.
asset_msg_t *
    asset_msg_recv_nowait (void *input);

//  Send the asset_msg to the output, and destroy it
int
    asset_msg_send (asset_msg_t **self_p, void *output);

//  Send the asset_msg to the output, and do not destroy it
int
    asset_msg_send_again (asset_msg_t *self, void *output);

//  Encode the ELEMENT 
zmsg_t *
    asset_msg_encode_element (
        const char *name,
        uint32_t location,
        byte location_type,
        byte type,
        zhash_t *ext);

//  Encode the DEVICE 
zmsg_t *
    asset_msg_encode_device (
        const char *device_type,
        zlist_t *groups,
        zlist_t *powers,
        const char *ip,
        const char *hostname,
        const char *fqdn,
        const char *mac,
        zmsg_t *msg);

//  Encode the GET_ELEMENT 
zmsg_t *
    asset_msg_encode_get_element (
        uint32_t element_id,
        byte type);

//  Encode the RETURN_ELEMENT 
zmsg_t *
    asset_msg_encode_return_element (
        uint32_t element_id,
        zmsg_t *msg);

//  Encode the UPDATE_ELEMENT 
zmsg_t *
    asset_msg_encode_update_element (
        uint32_t element_id,
        zmsg_t *msg);

//  Encode the INSERT_ELEMENT 
zmsg_t *
    asset_msg_encode_insert_element (
        zmsg_t *msg);

//  Encode the DELETE_ELEMENT 
zmsg_t *
    asset_msg_encode_delete_element (
        uint32_t element_id,
        byte type);

//  Encode the OK 
zmsg_t *
    asset_msg_encode_ok (
        uint32_t element_id);

//  Encode the FAIL 
zmsg_t *
    asset_msg_encode_fail (
        byte error_id);

//  Encode the GET_ELEMENTS 
zmsg_t *
    asset_msg_encode_get_elements (
        byte type);

//  Encode the RETURN_ELEMENTS 
zmsg_t *
    asset_msg_encode_return_elements (
        zhash_t *element_ids);

//  Encode the GET_LOCATION_FROM 
zmsg_t *
    asset_msg_encode_get_location_from (
        uint32_t element_id,
        byte recursive,
        byte filter_type);

//  Encode the GET_LOCATION_TO 
zmsg_t *
    asset_msg_encode_get_location_to (
        uint32_t element_id);

//  Encode the RETURN_LOCATION_TO 
zmsg_t *
    asset_msg_encode_return_location_to (
        uint32_t element_id,
        byte type,
        const char *name,
        const char *type_name,
        zmsg_t *msg);

//  Encode the RETURN_LOCATION_FROM 
zmsg_t *
    asset_msg_encode_return_location_from (
        uint32_t element_id,
        byte type,
        const char *name,
        const char *type_name,
        zframe_t *dcs,
        zframe_t *rooms,
        zframe_t *rows,
        zframe_t *racks,
        zframe_t *devices,
        zframe_t *grps);

//  Encode the GET_POWER_FROM 
zmsg_t *
    asset_msg_encode_get_power_from (
        uint32_t element_id);

//  Encode the POWERCHAIN_DEVICE 
zmsg_t *
    asset_msg_encode_powerchain_device (
        uint32_t element_id,
        const char *type_name,
        const char *name);

//  Encode the RETURN_POWER 
zmsg_t *
    asset_msg_encode_return_power (
        zframe_t *devices,
        zlist_t *powers);

//  Encode the GET_POWER_TO 
zmsg_t *
    asset_msg_encode_get_power_to (
        uint32_t element_id);

//  Encode the GET_POWER_GROUP 
zmsg_t *
    asset_msg_encode_get_power_group (
        uint32_t element_id);

//  Encode the GET_POWER_DATACENTER 
zmsg_t *
    asset_msg_encode_get_power_datacenter (
        uint32_t element_id);


//  Send the ELEMENT to the output in one step
//  WARNING, this call will fail if output is of type ZMQ_ROUTER.
int
    asset_msg_send_element (void *output,
        const char *name,
        uint32_t location,
        byte location_type,
        byte type,
        zhash_t *ext);
    
//  Send the DEVICE to the output in one step
//  WARNING, this call will fail if output is of type ZMQ_ROUTER.
int
    asset_msg_send_device (void *output,
        const char *device_type,
        zlist_t *groups,
        zlist_t *powers,
        const char *ip,
        const char *hostname,
        const char *fqdn,
        const char *mac,
        zmsg_t *msg);
    
//  Send the GET_ELEMENT to the output in one step
//  WARNING, this call will fail if output is of type ZMQ_ROUTER.
int
    asset_msg_send_get_element (void *output,
        uint32_t element_id,
        byte type);
    
//  Send the RETURN_ELEMENT to the output in one step
//  WARNING, this call will fail if output is of type ZMQ_ROUTER.
int
    asset_msg_send_return_element (void *output,
        uint32_t element_id,
        zmsg_t *msg);
    
//  Send the UPDATE_ELEMENT to the output in one step
//  WARNING, this call will fail if output is of type ZMQ_ROUTER.
int
    asset_msg_send_update_element (void *output,
        uint32_t element_id,
        zmsg_t *msg);
    
//  Send the INSERT_ELEMENT to the output in one step
//  WARNING, this call will fail if output is of type ZMQ_ROUTER.
int
    asset_msg_send_insert_element (void *output,
        zmsg_t *msg);
    
//  Send the DELETE_ELEMENT to the output in one step
//  WARNING, this call will fail if output is of type ZMQ_ROUTER.
int
    asset_msg_send_delete_element (void *output,
        uint32_t element_id,
        byte type);
    
//  Send the OK to the output in one step
//  WARNING, this call will fail if output is of type ZMQ_ROUTER.
int
    asset_msg_send_ok (void *output,
        uint32_t element_id);
    
//  Send the FAIL to the output in one step
//  WARNING, this call will fail if output is of type ZMQ_ROUTER.
int
    asset_msg_send_fail (void *output,
        byte error_id);
    
//  Send the GET_ELEMENTS to the output in one step
//  WARNING, this call will fail if output is of type ZMQ_ROUTER.
int
    asset_msg_send_get_elements (void *output,
        byte type);
    
//  Send the RETURN_ELEMENTS to the output in one step
//  WARNING, this call will fail if output is of type ZMQ_ROUTER.
int
    asset_msg_send_return_elements (void *output,
        zhash_t *element_ids);
    
//  Send the GET_LOCATION_FROM to the output in one step
//  WARNING, this call will fail if output is of type ZMQ_ROUTER.
int
    asset_msg_send_get_location_from (void *output,
        uint32_t element_id,
        byte recursive,
        byte filter_type);
    
//  Send the GET_LOCATION_TO to the output in one step
//  WARNING, this call will fail if output is of type ZMQ_ROUTER.
int
    asset_msg_send_get_location_to (void *output,
        uint32_t element_id);
    
//  Send the RETURN_LOCATION_TO to the output in one step
//  WARNING, this call will fail if output is of type ZMQ_ROUTER.
int
    asset_msg_send_return_location_to (void *output,
        uint32_t element_id,
        byte type,
        const char *name,
        const char *type_name,
        zmsg_t *msg);
    
//  Send the RETURN_LOCATION_FROM to the output in one step
//  WARNING, this call will fail if output is of type ZMQ_ROUTER.
int
    asset_msg_send_return_location_from (void *output,
        uint32_t element_id,
        byte type,
        const char *name,
        const char *type_name,
        zframe_t *dcs,
        zframe_t *rooms,
        zframe_t *rows,
        zframe_t *racks,
        zframe_t *devices,
        zframe_t *grps);
    
//  Send the GET_POWER_FROM to the output in one step
//  WARNING, this call will fail if output is of type ZMQ_ROUTER.
int
    asset_msg_send_get_power_from (void *output,
        uint32_t element_id);
    
//  Send the POWERCHAIN_DEVICE to the output in one step
//  WARNING, this call will fail if output is of type ZMQ_ROUTER.
int
    asset_msg_send_powerchain_device (void *output,
        uint32_t element_id,
        const char *type_name,
        const char *name);
    
//  Send the RETURN_POWER to the output in one step
//  WARNING, this call will fail if output is of type ZMQ_ROUTER.
int
    asset_msg_send_return_power (void *output,
        zframe_t *devices,
        zlist_t *powers);
    
//  Send the GET_POWER_TO to the output in one step
//  WARNING, this call will fail if output is of type ZMQ_ROUTER.
int
    asset_msg_send_get_power_to (void *output,
        uint32_t element_id);
    
//  Send the GET_POWER_GROUP to the output in one step
//  WARNING, this call will fail if output is of type ZMQ_ROUTER.
int
    asset_msg_send_get_power_group (void *output,
        uint32_t element_id);
    
//  Send the GET_POWER_DATACENTER to the output in one step
//  WARNING, this call will fail if output is of type ZMQ_ROUTER.
int
    asset_msg_send_get_power_datacenter (void *output,
        uint32_t element_id);
    
//  Duplicate the asset_msg message
asset_msg_t *
    asset_msg_dup (asset_msg_t *self);

//  Print contents of message to stdout
void
    asset_msg_print (asset_msg_t *self);

//  Get/set the message routing id
zframe_t *
    asset_msg_routing_id (asset_msg_t *self);
void
    asset_msg_set_routing_id (asset_msg_t *self, zframe_t *routing_id);

//  Get the asset_msg id and printable command
int
    asset_msg_id (asset_msg_t *self);
void
    asset_msg_set_id (asset_msg_t *self, int id);
const char *
    asset_msg_command (asset_msg_t *self);

//  Get/set the name field
const char *
    asset_msg_name (asset_msg_t *self);
void
    asset_msg_set_name (asset_msg_t *self, const char *format, ...);

//  Get/set the location field
uint32_t
    asset_msg_location (asset_msg_t *self);
void
    asset_msg_set_location (asset_msg_t *self, uint32_t location);

//  Get/set the location_type field
byte
    asset_msg_location_type (asset_msg_t *self);
void
    asset_msg_set_location_type (asset_msg_t *self, byte location_type);

//  Get/set the type field
byte
    asset_msg_type (asset_msg_t *self);
void
    asset_msg_set_type (asset_msg_t *self, byte type);

//  Get/set the ext field
zhash_t *
    asset_msg_ext (asset_msg_t *self);
//  Get the ext field and transfer ownership to caller
zhash_t *
    asset_msg_get_ext (asset_msg_t *self);
//  Set the ext field, transferring ownership from caller
void
    asset_msg_set_ext (asset_msg_t *self, zhash_t **ext_p);
    
//  Get/set a value in the ext dictionary
const char *
    asset_msg_ext_string (asset_msg_t *self,
        const char *key, const char *default_value);
uint64_t
    asset_msg_ext_number (asset_msg_t *self,
        const char *key, uint64_t default_value);
void
    asset_msg_ext_insert (asset_msg_t *self,
        const char *key, const char *format, ...);
size_t
    asset_msg_ext_size (asset_msg_t *self);

//  Get/set the device_type field
const char *
    asset_msg_device_type (asset_msg_t *self);
void
    asset_msg_set_device_type (asset_msg_t *self, const char *format, ...);

//  Get/set the groups field
zlist_t *
    asset_msg_groups (asset_msg_t *self);
//  Get the groups field and transfer ownership to caller
zlist_t *
    asset_msg_get_groups (asset_msg_t *self);
//  Set the groups field, transferring ownership from caller
void
    asset_msg_set_groups (asset_msg_t *self, zlist_t **groups_p);

//  Iterate through the groups field, and append a groups value
const char *
    asset_msg_groups_first (asset_msg_t *self);
const char *
    asset_msg_groups_next (asset_msg_t *self);
void
    asset_msg_groups_append (asset_msg_t *self, const char *format, ...);
size_t
    asset_msg_groups_size (asset_msg_t *self);

//  Get/set the powers field
zlist_t *
    asset_msg_powers (asset_msg_t *self);
//  Get the powers field and transfer ownership to caller
zlist_t *
    asset_msg_get_powers (asset_msg_t *self);
//  Set the powers field, transferring ownership from caller
void
    asset_msg_set_powers (asset_msg_t *self, zlist_t **powers_p);

//  Iterate through the powers field, and append a powers value
const char *
    asset_msg_powers_first (asset_msg_t *self);
const char *
    asset_msg_powers_next (asset_msg_t *self);
void
    asset_msg_powers_append (asset_msg_t *self, const char *format, ...);
size_t
    asset_msg_powers_size (asset_msg_t *self);

//  Get/set the ip field
const char *
    asset_msg_ip (asset_msg_t *self);
void
    asset_msg_set_ip (asset_msg_t *self, const char *format, ...);

//  Get/set the hostname field
const char *
    asset_msg_hostname (asset_msg_t *self);
void
    asset_msg_set_hostname (asset_msg_t *self, const char *format, ...);

//  Get/set the fqdn field
const char *
    asset_msg_fqdn (asset_msg_t *self);
void
    asset_msg_set_fqdn (asset_msg_t *self, const char *format, ...);

//  Get/set the mac field
const char *
    asset_msg_mac (asset_msg_t *self);
void
    asset_msg_set_mac (asset_msg_t *self, const char *format, ...);

//  Get a copy of the msg field
zmsg_t *
    asset_msg_msg (asset_msg_t *self);
//  Get the msg field and transfer ownership to caller
zmsg_t *
    asset_msg_get_msg (asset_msg_t *self);
//  Set the msg field, transferring ownership from caller
void
    asset_msg_set_msg (asset_msg_t *self, zmsg_t **msg_p);

//  Get/set the element_id field
uint32_t
    asset_msg_element_id (asset_msg_t *self);
void
    asset_msg_set_element_id (asset_msg_t *self, uint32_t element_id);

//  Get/set the error_id field
byte
    asset_msg_error_id (asset_msg_t *self);
void
    asset_msg_set_error_id (asset_msg_t *self, byte error_id);

//  Get/set the element_ids field
zhash_t *
    asset_msg_element_ids (asset_msg_t *self);
//  Get the element_ids field and transfer ownership to caller
zhash_t *
    asset_msg_get_element_ids (asset_msg_t *self);
//  Set the element_ids field, transferring ownership from caller
void
    asset_msg_set_element_ids (asset_msg_t *self, zhash_t **element_ids_p);
    
//  Get/set a value in the element_ids dictionary
const char *
    asset_msg_element_ids_string (asset_msg_t *self,
        const char *key, const char *default_value);
uint64_t
    asset_msg_element_ids_number (asset_msg_t *self,
        const char *key, uint64_t default_value);
void
    asset_msg_element_ids_insert (asset_msg_t *self,
        const char *key, const char *format, ...);
size_t
    asset_msg_element_ids_size (asset_msg_t *self);

//  Get/set the recursive field
byte
    asset_msg_recursive (asset_msg_t *self);
void
    asset_msg_set_recursive (asset_msg_t *self, byte recursive);

//  Get/set the filter_type field
byte
    asset_msg_filter_type (asset_msg_t *self);
void
    asset_msg_set_filter_type (asset_msg_t *self, byte filter_type);

//  Get/set the type_name field
const char *
    asset_msg_type_name (asset_msg_t *self);
void
    asset_msg_set_type_name (asset_msg_t *self, const char *format, ...);

//  Get a copy of the dcs field
zframe_t *
    asset_msg_dcs (asset_msg_t *self);
//  Get the dcs field and transfer ownership to caller
zframe_t *
    asset_msg_get_dcs (asset_msg_t *self);
//  Set the dcs field, transferring ownership from caller
void
    asset_msg_set_dcs (asset_msg_t *self, zframe_t **frame_p);

//  Get a copy of the rooms field
zframe_t *
    asset_msg_rooms (asset_msg_t *self);
//  Get the rooms field and transfer ownership to caller
zframe_t *
    asset_msg_get_rooms (asset_msg_t *self);
//  Set the rooms field, transferring ownership from caller
void
    asset_msg_set_rooms (asset_msg_t *self, zframe_t **frame_p);

//  Get a copy of the rows field
zframe_t *
    asset_msg_rows (asset_msg_t *self);
//  Get the rows field and transfer ownership to caller
zframe_t *
    asset_msg_get_rows (asset_msg_t *self);
//  Set the rows field, transferring ownership from caller
void
    asset_msg_set_rows (asset_msg_t *self, zframe_t **frame_p);

//  Get a copy of the racks field
zframe_t *
    asset_msg_racks (asset_msg_t *self);
//  Get the racks field and transfer ownership to caller
zframe_t *
    asset_msg_get_racks (asset_msg_t *self);
//  Set the racks field, transferring ownership from caller
void
    asset_msg_set_racks (asset_msg_t *self, zframe_t **frame_p);

//  Get a copy of the devices field
zframe_t *
    asset_msg_devices (asset_msg_t *self);
//  Get the devices field and transfer ownership to caller
zframe_t *
    asset_msg_get_devices (asset_msg_t *self);
//  Set the devices field, transferring ownership from caller
void
    asset_msg_set_devices (asset_msg_t *self, zframe_t **frame_p);

//  Get a copy of the grps field
zframe_t *
    asset_msg_grps (asset_msg_t *self);
//  Get the grps field and transfer ownership to caller
zframe_t *
    asset_msg_get_grps (asset_msg_t *self);
//  Set the grps field, transferring ownership from caller
void
    asset_msg_set_grps (asset_msg_t *self, zframe_t **frame_p);

//  Self test of this class
int
    asset_msg_test (bool verbose);
//  @end

//  For backwards compatibility with old codecs
#define asset_msg_dump      asset_msg_print

#ifdef __cplusplus
}
#endif

#endif
