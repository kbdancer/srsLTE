/**
 *
 * \section COPYRIGHT
 *
 * Copyright 2013-2014 The srsLTE Developers. See the
 * COPYRIGHT file at the top-level directory of this distribution.
 *
 * \section LICENSE
 *
 * This file is part of the srsLTE library.
 *
 * srsLTE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * srsLTE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * A copy of the GNU Lesser General Public License can be found in
 * the LICENSE file in the top-level directory of this distribution
 * and at http://www.gnu.org/licenses/.
 *
 */

#ifndef TURBODECODER_
#define TURBODECODER_

#include "srslte/config.h"
#include "srslte/fec/tc_interl.h"

#define RATE 3
#define TOTALTAIL 12

#define LOG18 -2.07944

#define NUMSTATES 8
#define NINPUTS 2
#define TAIL 3
#define TOTALTAIL 12

#define INF 9e4
#define ZERO 9e-4

#define MAX_LONG_CB     6144
#define MAX_LONG_CODED  (RATE*MAX_LONG_CB+TOTALTAIL)

typedef float llr_t;

typedef struct SRSLTE_API {
  int max_long_cb;
  llr_t *beta;
} map_gen_t;

typedef struct SRSLTE_API {
  int max_long_cb;

  map_gen_t dec;

  llr_t *llr1;
  llr_t *llr2;
  llr_t *w;
  llr_t *syst;
  llr_t *parity;

  tc_interl_t interleaver;
} tdec_t;

SRSLTE_API int tdec_init(tdec_t * h, 
                         uint32_t max_long_cb);

SRSLTE_API void tdec_free(tdec_t * h);

SRSLTE_API int tdec_reset(tdec_t * h, uint32_t long_cb);

SRSLTE_API void tdec_iteration(tdec_t * h, 
                               llr_t * input, 
                               uint32_t long_cb);

SRSLTE_API void tdec_decision(tdec_t * h, 
                              uint8_t *output, 
                              uint32_t long_cb);

SRSLTE_API int tdec_run_all(tdec_t * h, 
                             llr_t * input, 
                             uint8_t *output,
                             uint32_t nof_iterations, 
                             uint32_t long_cb);

#endif