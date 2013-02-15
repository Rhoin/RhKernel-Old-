/*
 * Last Update: 04.02.2013
 */

#ifndef _CMD_H_
#define _CMD_H_
#include <rhKernel/system.h>

typedef void (*cmd_func_t)(const char *cmd);
#define REG_CMD(func,id) register_cmd(func,id)
#define CALL_CMD(id) call_cmd(id)
/*
 * 
 * name: void register_cmd(cmd_func_t *fnc, int id)
 * @param fnc: Function pointer
 * @param str: String for function controll
 * 
 */
RHAPI void register_cmd(cmd_func_t fnc, int id);

/*
 * 
 * name: cmd_func_t *call_cmd(int id)
 * @param id: Id of command
 * @return Commands pointer
 * 
 */
RHAPI cmd_func_t call_cmd(int id);

/*
 * 
 * name: void getCmd(char *buff)
 * @param buff: Command will be written in buff
 * @param n: Count of command char
 * 
 */
RHAPI void getCmd(char *buff, int n);

/*
 * 
 * name: rhkbool parseCmd(char *buff)
 * @param buff: Buffer which contains command
 * @return If command is exit then It will return TRUE
 * 
 */
RHAPI rhkbool parseCmd(char *buff);
#endif /*_CMD_H_*/
