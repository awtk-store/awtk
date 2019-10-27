/**
 * File:   mutex.c
 * Author: AWTK Develop Team
 * Brief:  mutex base on tos_mutex
 *
 * Copyright (c) 2018 - 2019  Guangzhou ZHIYUAN Electronics Co.,Ltd.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * License file for more details.
 *
 */

/**
 * History:
 * ================================================================
 * 2019-10-20 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "tkc/mem.h"
#include "tkc/mutex.h"
#include "cmsis_os.h"

struct _tk_mutex_t {
  osMutexId mutex;
};

tk_mutex_t* tk_mutex_create() {
  osMutexDef_t def;
  tk_mutex_t* mutex = TKMEM_ZALLOC(tk_mutex_t);
  return_value_if_fail(mutex != NULL, NULL);

  memset(&def, 0x00, sizeof(def));
  mutex->mutex = osMutexCreate(&(def));
  if(mutex->mutex == NULL) {
    TKMEM_FREE(mutex);
  }

  return mutex;
}

ret_t tk_mutex_lock(tk_mutex_t* mutex) {
  return_value_if_fail(mutex != NULL, RET_BAD_PARAMS);

  return_value_if_fail(osMutexWait(mutex->mutex, 0xffffffff) == osOK, RET_FAIL);

  return RET_OK;
}

ret_t tk_mutex_unlock(tk_mutex_t* mutex) {
  return_value_if_fail(mutex != NULL, RET_BAD_PARAMS);

  return_value_if_fail(osMutexRelease(mutex->mutex) == osOK, RET_FAIL);

  return RET_OK;
}

ret_t tk_mutex_destroy(tk_mutex_t* mutex) {
  return_value_if_fail(mutex != NULL && mutex->mutex, RET_BAD_PARAMS);

  osMutexDelete(mutex->mutex);
  memset(mutex, 0x00, sizeof(tk_mutex_t));

  TKMEM_FREE(mutex);

  return RET_OK;
}
