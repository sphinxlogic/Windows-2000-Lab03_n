//
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//


//
// Define the severity codes
//


//
// MessageId: MSG_CANNOT_ENUM_ITEM
//
// MessageText:
//
//  Failed to enumerate stored item "%1" (err=%2!u!).
//
#define MSG_CANNOT_ENUM_ITEM             0x00000001L

//
// MessageId: MSG_CANNOT_GET_DESCRIPTION
//
// MessageText:
//
//  Could not get item description of ID:%1!05x! (err=%2!u!).
//
#define MSG_CANNOT_GET_DESCRIPTION       0x00000002L

//
// MessageId: MSG_CANNOT_ALLOC_MEMORY
//
// MessageText:
//
//  Could not allocate memory in %1, size=%2!u! (err=%3!u!).
//
#define MSG_CANNOT_ALLOC_MEMORY          0x00000003L

//
// MessageId: MSG_CANNOT_ENUM_TYPE
//
// MessageText:
//
//  Failed to enumerate type "%1" (err=%2!u!).
//
#define MSG_CANNOT_ENUM_TYPE             0x00000004L

//
// MessageId: MSG_CANNOT_GET_TYPEINFO
//
// MessageText:
//
//  Could not get type information of Handle:%1!08x! (err=%2!u!).
//
#define MSG_CANNOT_GET_TYPEINFO          0x00000005L

//
// MessageId: MSG_CANNOT_GET_ITEMINFO
//
// MessageText:
//
//  Could not get item information of ID:%1!05x! (err=%2!u!).
//
#define MSG_CANNOT_GET_ITEMINFO          0x00000006L

//
// MessageId: MSG_CANNOT_ENUM_LINK
//
// MessageText:
//
//  Failed to enumerate linked item with ID:%1!05x! (err=%2!u!).
//
#define MSG_CANNOT_ENUM_LINK             0x00000007L

//
// MessageId: MSG_MISC_ROUTINE_FAIL
//
// MessageText:
//
//  %1 failed (err=%2!u!).
//
#define MSG_MISC_ROUTINE_FAIL            0x00000008L

//
// MessageId: MSG_FAIL_PARSE_COMMAND_LINE
//
// MessageText:
//
//  Failed in CommandLineToArgvW, %1 (err=%2!u!).
//
#define MSG_FAIL_PARSE_COMMAND_LINE      0x00000009L

//
// MessageId: MSG_TITLE_TYPE_CMD
//
// MessageText:
//
//  Handle   Type Name                                          Support Plug-in
//  ---------------------------------------------------------------------------
//
#define MSG_TITLE_TYPE_CMD               0x0000000AL

//
// MessageId: MSG_TYPE_INFO
//
// MessageText:
//
//  %1!08x! %2!-50s! %3!-s!
//
#define MSG_TYPE_INFO                    0x0000000BL

//
// MessageId: MSG_ALLOWED_CONTAINER_TYPES
//
// MessageText:
//
//  Allowed container types
//
#define MSG_ALLOWED_CONTAINER_TYPES      0x0000000CL

//
// MessageId: MSG_TITLE_VIEW_ITEM_CMD
//
// MessageText:
//
//  Reported Item
//  ---------------------------------------------------------------------------
//
#define MSG_TITLE_VIEW_ITEM_CMD          0x0000000DL

//
// MessageId: MSG_ITEM_INFO
//
// MessageText:
//
//  @%1!08x!:%2!05x! (ID:%3!05x!) %4!-30s! by %5
//
#define MSG_ITEM_INFO                    0x0000000EL

//
// MessageId: MSG_TITLE_DESC_ITEM_CMD
//
// MessageText:
//
//  
//
#define MSG_TITLE_DESC_ITEM_CMD          0x0000000FL

//
// MessageId: MSG_TITLE_DESC_TYPE
//
// MessageText:
//
//  Description of Type
//  ---------------------------------------------------------------------------
//
#define MSG_TITLE_DESC_TYPE              0x00000010L

//
// MessageId: MSG_LINE
//
// MessageText:
//
//  ---------------------------------------------------------------------------
//
#define MSG_LINE                         0x00000011L

//
// MessageId: MSG_ITEM_START_LINK
//
// MessageText:
//
//  %1 @%2!08x! (ID:%3!05x!, Reported by %4)
//
#define MSG_ITEM_START_LINK              0x00000012L

//
// MessageId: MSG_LINK_ITEM
//
// MessageText:
//
//  %1 @%2!08x! (ID:%3!05x!, Linked by %4)
//
#define MSG_LINK_ITEM                    0x00000013L

//
// MessageId: MSG_HELP
//
// MessageText:
//
//  
//  type [type_name] [-h type_handle]
//     - display registered types.
//  
//       type_name   Specify type name string. You can use '*(asterisk)' as a wild
//                   card at the end of string. If you use a wild card, every
//                   matched type information is enumerated in short form. If full
//                   type_name is specified, display type information in detail.
//       -h          Specify a hexadecimal type handle.
//  
//  find [type_name] [start_addr [end_addr] [-o]] [-v]
//     - find located item by type_name or  memory range.
//  
//       type_name   Specify type name string. You can use '*(asterisk)' as a wild
//                   card at the end of string.
//       start_addr  Hexadecimal start address of memory range. Default is 0. If
//                   you omit both start_addr and end_addr, memory range becomes
//                   whole virtual address.
//       end_addr    Hexadecimal end address of memory range. If you specify
//                   start_addr only, end_addr becomes the same as start_addr.
//       -o          Display all items that overlap with specified memory range.
//       -v          Display formatted description of each item.
//  
//  view item_id
//     - display item information and formatted description.
//  
//       item_id     Hexadecimal value of item ID.
//  
//  link item_id [depth] [-{b|f|m}]
//     - display linked items.
//  
//       item_id     Hexadecimal value of item ID.
//       depth       Specify nesting level of link. Default nesting level is 1.
//       -b          Display items from which an item links.
//       -f          Display items to which an item links.
//       -m          Display items with which an item links (forward and backward).
//  
//  d{b|d} [address] [length]
//     - hexadecimal dump of given range.
//  
//       address     Hexadecimal start address of memory range.
//       length      Hexadecimal length of memory range.
//  
//  help, ?
//     - show this help.
//  
//  exit
//     - exit from command mode.
//
#define MSG_HELP                         0x00000014L

