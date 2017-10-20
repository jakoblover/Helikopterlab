/*
 * P2p2.c
 *
 * Code generation for model "P2p2".
 *
 * Model version              : 1.118
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Sat Oct 21 00:41:41 2017
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "P2p2.h"
#include "P2p2_private.h"
#include "P2p2_dt.h"

/* Block signals (auto storage) */
B_P2p2_T P2p2_B;

/* Continuous states */
X_P2p2_T P2p2_X;

/* Block states (auto storage) */
DW_P2p2_T P2p2_DW;

/* Real-time model */
RT_MODEL_P2p2_T P2p2_M_;
RT_MODEL_P2p2_T *const P2p2_M = &P2p2_M_;

/*
 * Writes out MAT-file header.  Returns success or failure.
 * Returns:
 *      0 - success
 *      1 - failure
 */
int_T rt_WriteMat4FileHeader(FILE *fp, int32_T m, int32_T n, const char *name)
{
  typedef enum { ELITTLE_ENDIAN, EBIG_ENDIAN } ByteOrder;

  int16_T one = 1;
  ByteOrder byteOrder = (*((int8_T *)&one)==1) ? ELITTLE_ENDIAN : EBIG_ENDIAN;
  int32_T type = (byteOrder == ELITTLE_ENDIAN) ? 0: 1000;
  int32_T imagf = 0;
  int32_T name_len = (int32_T)strlen(name) + 1;
  if ((fwrite(&type, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&m, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&n, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&imagf, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&name_len, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(name, sizeof(char), name_len, fp) == 0)) {
    return(1);
  } else {
    return(0);
  }
}                                      /* end rt_WriteMat4FileHeader */

/*
 * This function updates continuous states using the ODE1 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = (ODE1_IntgData *)rtsiGetSolverData(si);
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 4;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  P2p2_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; i++) {
    *x += h * f0[i];
    x++;
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void P2p2_output(void)
{
  /* local block i/o variables */
  real_T rtb_Backgain;
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_TmpSignalConversionAtToFile[6];
  real_T rtb_TmpSignalConversionAtToFi_n[2];
  real_T rtb_DeadZoney;
  real_T rtb_Sum_mn;
  real_T rtb_Frontgain;
  real_T rtb_Add;
  if (rtmIsMajorTimeStep(P2p2_M)) {
    /* set solver stop time */
    if (!(P2p2_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&P2p2_M->solverInfo, ((P2p2_M->Timing.clockTickH0 +
        1) * P2p2_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&P2p2_M->solverInfo, ((P2p2_M->Timing.clockTick0 + 1)
        * P2p2_M->Timing.stepSize0 + P2p2_M->Timing.clockTickH0 *
        P2p2_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(P2p2_M)) {
    P2p2_M->Timing.t[0] = rtsiGetT(&P2p2_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(P2p2_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S3>/HIL Read Encoder Timebase' */

    /* S-Function Block: P2p2/Heli 3D/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder(P2p2_DW.HILReadEncoderTimebase_Task, 1,
        &P2p2_DW.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P2p2_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 = P2p2_DW.HILReadEncoderTimebase_Buffer[0];
        rtb_DeadZoney = P2p2_DW.HILReadEncoderTimebase_Buffer[1];
        rtb_Sum_mn = P2p2_DW.HILReadEncoderTimebase_Buffer[2];
      }
    }

    /* Gain: '<S3>/Pitch: Count to rad' */
    P2p2_B.PitchCounttorad = P2p2_P.PitchCounttorad_Gain * rtb_DeadZoney;

    /* Gain: '<S3>/Deg to Rad   ' incorporates:
     *  Gain: '<S10>/Gain'
     */
    P2p2_B.DegtoRad = P2p2_P.Gain_Gain * P2p2_B.PitchCounttorad *
      P2p2_P.DegtoRad_Gain;
  }

  /* Gain: '<S3>/Deg to Rad    ' incorporates:
   *  Gain: '<S11>/Gain'
   *  TransferFcn: '<S3>/Pitch: Transfer Fcn'
   */
  P2p2_B.DegtoRad_o = (P2p2_P.PitchTransferFcn_C *
                       P2p2_X.PitchTransferFcn_CSTATE +
                       P2p2_P.PitchTransferFcn_D * P2p2_B.PitchCounttorad) *
    P2p2_P.Gain_Gain_c * P2p2_P.DegtoRad_Gain_m;
  if (rtmIsMajorTimeStep(P2p2_M)) {
    /* Gain: '<S3>/Elevation: Count to rad' */
    P2p2_B.ElevationCounttorad = P2p2_P.ElevationCounttorad_Gain * rtb_Sum_mn;

    /* Gain: '<S3>/Deg to Rad     ' incorporates:
     *  Constant: '<S3>/Constant'
     *  Gain: '<S8>/Gain'
     *  Sum: '<S3>/Sum'
     */
    P2p2_B.DegtoRad_oh = (P2p2_P.Gain_Gain_i * P2p2_B.ElevationCounttorad +
                          P2p2_P.Constant_Value) * P2p2_P.DegtoRad_Gain_k;
  }

  /* Gain: '<S3>/Deg to Rad      ' incorporates:
   *  Gain: '<S9>/Gain'
   *  TransferFcn: '<S3>/Elevation: Transfer Fcn'
   */
  P2p2_B.DegtoRad_i = (P2p2_P.ElevationTransferFcn_C *
                       P2p2_X.ElevationTransferFcn_CSTATE +
                       P2p2_P.ElevationTransferFcn_D *
                       P2p2_B.ElevationCounttorad) * P2p2_P.Gain_Gain_o *
    P2p2_P.DegtoRad_Gain_d;
  if (rtmIsMajorTimeStep(P2p2_M)) {
    /* Gain: '<S3>/Travel: Count to rad' */
    P2p2_B.TravelCounttorad = P2p2_P.TravelCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o1;

    /* Gain: '<S3>/Deg to Rad' incorporates:
     *  Gain: '<S12>/Gain'
     */
    P2p2_B.DegtoRad_l = P2p2_P.Gain_Gain_k * P2p2_B.TravelCounttorad *
      P2p2_P.DegtoRad_Gain_kg;
  }

  /* Gain: '<S3>/Deg to Rad  ' incorporates:
   *  Gain: '<S13>/Gain'
   *  TransferFcn: '<S3>/Travel: Transfer Fcn'
   */
  P2p2_B.DegtoRad_j = (P2p2_P.TravelTransferFcn_C *
                       P2p2_X.TravelTransferFcn_CSTATE +
                       P2p2_P.TravelTransferFcn_D * P2p2_B.TravelCounttorad) *
    P2p2_P.Gain_Gain_b * P2p2_P.DegtoRad_Gain_f;
  if (rtmIsMajorTimeStep(P2p2_M)) {
    /* SignalConversion: '<Root>/TmpSignal ConversionAtTo FileInport1' */
    rtb_TmpSignalConversionAtToFile[0] = P2p2_B.DegtoRad;
    rtb_TmpSignalConversionAtToFile[1] = P2p2_B.DegtoRad_o;
    rtb_TmpSignalConversionAtToFile[2] = P2p2_B.DegtoRad_oh;
    rtb_TmpSignalConversionAtToFile[3] = P2p2_B.DegtoRad_i;
    rtb_TmpSignalConversionAtToFile[4] = P2p2_B.DegtoRad_l;
    rtb_TmpSignalConversionAtToFile[5] = P2p2_B.DegtoRad_j;

    /* ToFile: '<Root>/To File' */
    {
      if (!(++P2p2_DW.ToFile_IWORK.Decimation % 1) &&
          (P2p2_DW.ToFile_IWORK.Count*7)+1 < 100000000 ) {
        FILE *fp = (FILE *) P2p2_DW.ToFile_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[7];
          P2p2_DW.ToFile_IWORK.Decimation = 0;
          u[0] = P2p2_M->Timing.t[1];
          u[1] = rtb_TmpSignalConversionAtToFile[0];
          u[2] = rtb_TmpSignalConversionAtToFile[1];
          u[3] = rtb_TmpSignalConversionAtToFile[2];
          u[4] = rtb_TmpSignalConversionAtToFile[3];
          u[5] = rtb_TmpSignalConversionAtToFile[4];
          u[6] = rtb_TmpSignalConversionAtToFile[5];
          if (fwrite(u, sizeof(real_T), 7, fp) != 7) {
            rtmSetErrorStatus(P2p2_M, "Error writing to MAT-file var.mat");
            return;
          }

          if (((++P2p2_DW.ToFile_IWORK.Count)*7)+1 >= 100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file var.mat.\n");
          }
        }
      }
    }

    /* S-Function (game_controller_block): '<S4>/Game Controller' */

    /* S-Function Block: P2p2/Joystick/Game Controller (game_controller_block) */
    {
      if (P2p2_P.GameController_Enabled) {
        t_game_controller_states state;
        t_boolean new_data;
        t_error result;
        result = game_controller_poll(P2p2_DW.GameController_Controller, &state,
          &new_data);
        if (result == 0) {
          rtb_Sum_mn = state.x;
          rtb_DeadZoney = state.y;
        }
      } else {
        rtb_Sum_mn = 0;
        rtb_DeadZoney = 0;
      }
    }

    /* DeadZone: '<S4>/Dead Zone: x' */
    if (rtb_Sum_mn > P2p2_P.DeadZonex_End) {
      rtb_Sum_mn -= P2p2_P.DeadZonex_End;
    } else if (rtb_Sum_mn >= P2p2_P.DeadZonex_Start) {
      rtb_Sum_mn = 0.0;
    } else {
      rtb_Sum_mn -= P2p2_P.DeadZonex_Start;
    }

    /* End of DeadZone: '<S4>/Dead Zone: x' */

    /* Gain: '<S4>/Joystick_gain_x' incorporates:
     *  Gain: '<S4>/Gain: x'
     */
    P2p2_B.Joystick_gain_x = P2p2_P.Gainx_Gain * rtb_Sum_mn *
      P2p2_P.Joystick_gain_x;

    /* DeadZone: '<S4>/Dead Zone: y' */
    if (rtb_DeadZoney > P2p2_P.DeadZoney_End) {
      rtb_DeadZoney -= P2p2_P.DeadZoney_End;
    } else if (rtb_DeadZoney >= P2p2_P.DeadZoney_Start) {
      rtb_DeadZoney = 0.0;
    } else {
      rtb_DeadZoney -= P2p2_P.DeadZoney_Start;
    }

    /* End of DeadZone: '<S4>/Dead Zone: y' */

    /* Gain: '<S4>/Joystick_gain_y' incorporates:
     *  Gain: '<S4>/Gain: y'
     */
    P2p2_B.Joystick_gain_y = P2p2_P.Gainy_Gain * rtb_DeadZoney *
      P2p2_P.Joystick_gain_y;

    /* SignalConversion: '<Root>/TmpSignal ConversionAtTo File1Inport1' */
    rtb_TmpSignalConversionAtToFi_n[0] = P2p2_B.Joystick_gain_x;
    rtb_TmpSignalConversionAtToFi_n[1] = P2p2_B.Joystick_gain_y;

    /* ToFile: '<Root>/To File1' */
    {
      if (!(++P2p2_DW.ToFile1_IWORK.Decimation % 1) &&
          (P2p2_DW.ToFile1_IWORK.Count*3)+1 < 100000000 ) {
        FILE *fp = (FILE *) P2p2_DW.ToFile1_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[3];
          P2p2_DW.ToFile1_IWORK.Decimation = 0;
          u[0] = P2p2_M->Timing.t[1];
          u[1] = rtb_TmpSignalConversionAtToFi_n[0];
          u[2] = rtb_TmpSignalConversionAtToFi_n[1];
          if (fwrite(u, sizeof(real_T), 3, fp) != 3) {
            rtmSetErrorStatus(P2p2_M, "Error writing to MAT-file joystick.mat");
            return;
          }

          if (((++P2p2_DW.ToFile1_IWORK.Count)*3)+1 >= 100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file joystick.mat.\n");
          }
        }
      }
    }

    /* Gain: '<Root>/Gain1' */
    P2p2_B.Gain1 = P2p2_P.Gain1_Gain * P2p2_B.Joystick_gain_x;
  }

  /* Sum: '<S6>/Sum1' incorporates:
   *  Gain: '<S5>/k_rp'
   *  Gain: '<S6>/Gain'
   *  Gain: '<S6>/Gain1'
   *  Sum: '<S5>/Sum1'
   *  Sum: '<S6>/Sum'
   */
  rtb_Frontgain = ((P2p2_B.Gain1 - P2p2_B.DegtoRad_j) * P2p2_P.k_rp -
                   P2p2_B.DegtoRad) * P2p2_P.k_pp - P2p2_P.k_pd *
    P2p2_B.DegtoRad_o;

  /* Integrator: '<S7>/Integrator'
   *
   * Regarding '<S7>/Integrator':
   *  Limited Integrator
   */
  if (P2p2_X.Integrator_CSTATE >= P2p2_P.Integrator_UpperSat ) {
    P2p2_X.Integrator_CSTATE = P2p2_P.Integrator_UpperSat;
  } else if (P2p2_X.Integrator_CSTATE <= (P2p2_P.Integrator_LowerSat) ) {
    P2p2_X.Integrator_CSTATE = (P2p2_P.Integrator_LowerSat);
  }

  rtb_Backgain = P2p2_X.Integrator_CSTATE;
  if (rtmIsMajorTimeStep(P2p2_M)) {
    /* Sum: '<S2>/Sum' incorporates:
     *  Constant: '<Root>/Constant'
     */
    rtb_Sum_mn = P2p2_P.Constant_Value_m - P2p2_B.DegtoRad_oh;

    /* Gain: '<S7>/K_ep' */
    P2p2_B.K_ep = P2p2_P.K_ep_Gain * rtb_Sum_mn;
  }

  /* Sum: '<Root>/Sum2' incorporates:
   *  Constant: '<Root>/V*_s'
   *  Gain: '<S7>/K_ed'
   *  Sum: '<S7>/Sum'
   */
  rtb_Backgain = ((rtb_Backgain + P2p2_B.K_ep) - P2p2_P.K_ed_Gain *
                  P2p2_B.DegtoRad_i) + -P2p2_P.l_2 / P2p2_P.l_3;

  /* Sum: '<S1>/Add' */
  rtb_Add = rtb_Frontgain + rtb_Backgain;

  /* Gain: '<S1>/Back gain' incorporates:
   *  Sum: '<S1>/Subtract'
   */
  rtb_Backgain = (rtb_Backgain - rtb_Frontgain) * P2p2_P.Backgain_Gain;
  if (rtmIsMajorTimeStep(P2p2_M)) {
    /* Gain: '<S7>/K_ei' */
    P2p2_B.K_ei = P2p2_P.K_ei_Gain * rtb_Sum_mn;
  }

  /* Gain: '<S1>/Front gain' */
  rtb_Frontgain = P2p2_P.Frontgain_Gain * rtb_Add;

  /* Saturate: '<S3>/Front motor: Saturation' */
  if (rtb_Frontgain > P2p2_P.FrontmotorSaturation_UpperSat) {
    P2p2_B.FrontmotorSaturation = P2p2_P.FrontmotorSaturation_UpperSat;
  } else if (rtb_Frontgain < P2p2_P.FrontmotorSaturation_LowerSat) {
    P2p2_B.FrontmotorSaturation = P2p2_P.FrontmotorSaturation_LowerSat;
  } else {
    P2p2_B.FrontmotorSaturation = rtb_Frontgain;
  }

  /* End of Saturate: '<S3>/Front motor: Saturation' */

  /* Saturate: '<S3>/Back motor: Saturation' */
  if (rtb_Backgain > P2p2_P.BackmotorSaturation_UpperSat) {
    P2p2_B.BackmotorSaturation = P2p2_P.BackmotorSaturation_UpperSat;
  } else if (rtb_Backgain < P2p2_P.BackmotorSaturation_LowerSat) {
    P2p2_B.BackmotorSaturation = P2p2_P.BackmotorSaturation_LowerSat;
  } else {
    P2p2_B.BackmotorSaturation = rtb_Backgain;
  }

  /* End of Saturate: '<S3>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(P2p2_M)) {
    /* S-Function (hil_write_analog_block): '<S3>/HIL Write Analog' */

    /* S-Function Block: P2p2/Heli 3D/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      P2p2_DW.HILWriteAnalog_Buffer[0] = P2p2_B.FrontmotorSaturation;
      P2p2_DW.HILWriteAnalog_Buffer[1] = P2p2_B.BackmotorSaturation;
      result = hil_write_analog(P2p2_DW.HILInitialize_Card,
        P2p2_P.HILWriteAnalog_channels, 2, &P2p2_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P2p2_M, _rt_error_message);
      }
    }
  }
}

/* Model update function */
void P2p2_update(void)
{
  if (rtmIsMajorTimeStep(P2p2_M)) {
    rt_ertODEUpdateContinuousStates(&P2p2_M->solverInfo);
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++P2p2_M->Timing.clockTick0)) {
    ++P2p2_M->Timing.clockTickH0;
  }

  P2p2_M->Timing.t[0] = rtsiGetSolverStopTime(&P2p2_M->solverInfo);

  {
    /* Update absolute timer for sample time: [0.01s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++P2p2_M->Timing.clockTick1)) {
      ++P2p2_M->Timing.clockTickH1;
    }

    P2p2_M->Timing.t[1] = P2p2_M->Timing.clockTick1 * P2p2_M->Timing.stepSize1 +
      P2p2_M->Timing.clockTickH1 * P2p2_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void P2p2_derivatives(void)
{
  XDot_P2p2_T *_rtXdot;
  _rtXdot = ((XDot_P2p2_T *) P2p2_M->ModelData.derivs);

  /* Derivatives for TransferFcn: '<S3>/Pitch: Transfer Fcn' */
  _rtXdot->PitchTransferFcn_CSTATE = 0.0;
  _rtXdot->PitchTransferFcn_CSTATE += P2p2_P.PitchTransferFcn_A *
    P2p2_X.PitchTransferFcn_CSTATE;
  _rtXdot->PitchTransferFcn_CSTATE += P2p2_B.PitchCounttorad;

  /* Derivatives for TransferFcn: '<S3>/Elevation: Transfer Fcn' */
  _rtXdot->ElevationTransferFcn_CSTATE = 0.0;
  _rtXdot->ElevationTransferFcn_CSTATE += P2p2_P.ElevationTransferFcn_A *
    P2p2_X.ElevationTransferFcn_CSTATE;
  _rtXdot->ElevationTransferFcn_CSTATE += P2p2_B.ElevationCounttorad;

  /* Derivatives for TransferFcn: '<S3>/Travel: Transfer Fcn' */
  _rtXdot->TravelTransferFcn_CSTATE = 0.0;
  _rtXdot->TravelTransferFcn_CSTATE += P2p2_P.TravelTransferFcn_A *
    P2p2_X.TravelTransferFcn_CSTATE;
  _rtXdot->TravelTransferFcn_CSTATE += P2p2_B.TravelCounttorad;

  /* Derivatives for Integrator: '<S7>/Integrator' */
  {
    boolean_T lsat;
    boolean_T usat;
    lsat = ( P2p2_X.Integrator_CSTATE <= (P2p2_P.Integrator_LowerSat) );
    usat = ( P2p2_X.Integrator_CSTATE >= P2p2_P.Integrator_UpperSat );
    if ((!lsat && !usat) ||
        (lsat && (P2p2_B.K_ei > 0)) ||
        (usat && (P2p2_B.K_ei < 0)) ) {
      ((XDot_P2p2_T *) P2p2_M->ModelData.derivs)->Integrator_CSTATE =
        P2p2_B.K_ei;
    } else {
      /* in saturation */
      ((XDot_P2p2_T *) P2p2_M->ModelData.derivs)->Integrator_CSTATE = 0.0;
    }
  }
}

/* Model initialize function */
void P2p2_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: P2p2/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &P2p2_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(P2p2_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(P2p2_DW.HILInitialize_Card,
      "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(P2p2_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(P2p2_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(P2p2_M, _rt_error_message);
      return;
    }

    if ((P2p2_P.HILInitialize_set_analog_input_ && !is_switching) ||
        (P2p2_P.HILInitialize_set_analog_inpu_o && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &P2p2_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = P2p2_P.HILInitialize_analog_input_mini;
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &P2p2_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = P2p2_P.HILInitialize_analog_input_maxi;
        }
      }

      result = hil_set_analog_input_ranges(P2p2_DW.HILInitialize_Card,
        P2p2_P.HILInitialize_analog_input_chan, 8U,
        &P2p2_DW.HILInitialize_AIMinimums[0], &P2p2_DW.HILInitialize_AIMaximums
        [0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P2p2_M, _rt_error_message);
        return;
      }
    }

    if ((P2p2_P.HILInitialize_set_analog_output && !is_switching) ||
        (P2p2_P.HILInitialize_set_analog_outp_d && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &P2p2_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = P2p2_P.HILInitialize_analog_output_min;
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &P2p2_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = P2p2_P.HILInitialize_analog_output_max;
        }
      }

      result = hil_set_analog_output_ranges(P2p2_DW.HILInitialize_Card,
        P2p2_P.HILInitialize_analog_output_cha, 8U,
        &P2p2_DW.HILInitialize_AOMinimums[0], &P2p2_DW.HILInitialize_AOMaximums
        [0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P2p2_M, _rt_error_message);
        return;
      }
    }

    if ((P2p2_P.HILInitialize_set_analog_outp_e && !is_switching) ||
        (P2p2_P.HILInitialize_set_analog_outp_k && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &P2p2_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = P2p2_P.HILInitialize_initial_analog_ou;
        }
      }

      result = hil_write_analog(P2p2_DW.HILInitialize_Card,
        P2p2_P.HILInitialize_analog_output_cha, 8U,
        &P2p2_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P2p2_M, _rt_error_message);
        return;
      }
    }

    if (P2p2_P.HILInitialize_set_analog_outp_o) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &P2p2_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = P2p2_P.HILInitialize_watchdog_analog_o;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (P2p2_DW.HILInitialize_Card, P2p2_P.HILInitialize_analog_output_cha, 8U,
         &P2p2_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P2p2_M, _rt_error_message);
        return;
      }
    }

    if ((P2p2_P.HILInitialize_set_encoder_param && !is_switching) ||
        (P2p2_P.HILInitialize_set_encoder_par_k && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes = &P2p2_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = P2p2_P.HILInitialize_quadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode(P2p2_DW.HILInitialize_Card,
        P2p2_P.HILInitialize_encoder_channels, 8U, (t_encoder_quadrature_mode *)
        &P2p2_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P2p2_M, _rt_error_message);
        return;
      }
    }

    if ((P2p2_P.HILInitialize_set_encoder_count && !is_switching) ||
        (P2p2_P.HILInitialize_set_encoder_cou_g && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts = &P2p2_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = P2p2_P.HILInitialize_initial_encoder_c;
        }
      }

      result = hil_set_encoder_counts(P2p2_DW.HILInitialize_Card,
        P2p2_P.HILInitialize_encoder_channels, 8U,
        &P2p2_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P2p2_M, _rt_error_message);
        return;
      }
    }

    if ((P2p2_P.HILInitialize_set_pwm_params_at && !is_switching) ||
        (P2p2_P.HILInitialize_set_pwm_params__m && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues = &P2p2_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = P2p2_P.HILInitialize_pwm_modes;
        }
      }

      result = hil_set_pwm_mode(P2p2_DW.HILInitialize_Card,
        P2p2_P.HILInitialize_pwm_channels, 8U, (t_pwm_mode *)
        &P2p2_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P2p2_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_pwm_channels =
          P2p2_P.HILInitialize_pwm_channels;
        int32_T *dw_POModeValues = &P2p2_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE) {
            P2p2_DW.HILInitialize_POSortedChans[num_duty_cycle_modes] =
              p_HILInitialize_pwm_channels[i1];
            P2p2_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes] =
              P2p2_P.HILInitialize_pwm_frequency;
            num_duty_cycle_modes++;
          } else {
            P2p2_DW.HILInitialize_POSortedChans[7U - num_frequency_modes] =
              p_HILInitialize_pwm_channels[i1];
            P2p2_DW.HILInitialize_POSortedFreqs[7U - num_frequency_modes] =
              P2p2_P.HILInitialize_pwm_frequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(P2p2_DW.HILInitialize_Card,
          &P2p2_DW.HILInitialize_POSortedChans[0], num_duty_cycle_modes,
          &P2p2_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(P2p2_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(P2p2_DW.HILInitialize_Card,
          &P2p2_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &P2p2_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(P2p2_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues = &P2p2_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = P2p2_P.HILInitialize_pwm_configuration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues = &P2p2_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = P2p2_P.HILInitialize_pwm_alignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals = &P2p2_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = P2p2_P.HILInitialize_pwm_polarity;
        }
      }

      result = hil_set_pwm_configuration(P2p2_DW.HILInitialize_Card,
        P2p2_P.HILInitialize_pwm_channels, 8U,
        (t_pwm_configuration *) &P2p2_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &P2p2_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &P2p2_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P2p2_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs = &P2p2_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = P2p2_P.HILInitialize_pwm_leading_deadb;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &P2p2_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = P2p2_P.HILInitialize_pwm_trailing_dead;
        }
      }

      result = hil_set_pwm_deadband(P2p2_DW.HILInitialize_Card,
        P2p2_P.HILInitialize_pwm_channels, 8U,
        &P2p2_DW.HILInitialize_POSortedFreqs[0],
        &P2p2_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P2p2_M, _rt_error_message);
        return;
      }
    }

    if ((P2p2_P.HILInitialize_set_pwm_outputs_a && !is_switching) ||
        (P2p2_P.HILInitialize_set_pwm_outputs_c && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &P2p2_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = P2p2_P.HILInitialize_initial_pwm_outpu;
        }
      }

      result = hil_write_pwm(P2p2_DW.HILInitialize_Card,
        P2p2_P.HILInitialize_pwm_channels, 8U, &P2p2_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P2p2_M, _rt_error_message);
        return;
      }
    }

    if (P2p2_P.HILInitialize_set_pwm_outputs_o) {
      {
        int_T i1;
        real_T *dw_POValues = &P2p2_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = P2p2_P.HILInitialize_watchdog_pwm_outp;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state(P2p2_DW.HILInitialize_Card,
        P2p2_P.HILInitialize_pwm_channels, 8U, &P2p2_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P2p2_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S3>/HIL Read Encoder Timebase' */

  /* S-Function Block: P2p2/Heli 3D/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader(P2p2_DW.HILInitialize_Card,
      P2p2_P.HILReadEncoderTimebase_samples_,
      P2p2_P.HILReadEncoderTimebase_channels, 3,
      &P2p2_DW.HILReadEncoderTimebase_Task);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(P2p2_M, _rt_error_message);
    }
  }

  /* Start for ToFile: '<Root>/To File' */
  {
    char fileName[509] = "var.mat";
    FILE *fp = (NULL);
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(P2p2_M, "Error creating .mat file var.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,7,0,"var")) {
      rtmSetErrorStatus(P2p2_M, "Error writing mat file header to file var.mat");
      return;
    }

    P2p2_DW.ToFile_IWORK.Count = 0;
    P2p2_DW.ToFile_IWORK.Decimation = -1;
    P2p2_DW.ToFile_PWORK.FilePtr = fp;
  }

  /* Start for S-Function (game_controller_block): '<S4>/Game Controller' */

  /* S-Function Block: P2p2/Joystick/Game Controller (game_controller_block) */
  {
    if (P2p2_P.GameController_Enabled) {
      t_double deadzone[6];
      t_double saturation[6];
      t_int index;
      t_error result;
      for (index = 0; index < 6; index++) {
        deadzone[index] = -1;
      }

      for (index = 0; index < 6; index++) {
        saturation[index] = -1;
      }

      result = game_controller_open(P2p2_P.GameController_ControllerNumber,
        P2p2_P.GameController_BufferSize, deadzone, saturation,
        P2p2_P.GameController_AutoCenter, 0, 1.0,
        &P2p2_DW.GameController_Controller);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P2p2_M, _rt_error_message);
      }
    }
  }

  /* Start for ToFile: '<Root>/To File1' */
  {
    char fileName[509] = "joystick.mat";
    FILE *fp = (NULL);
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(P2p2_M, "Error creating .mat file joystick.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,3,0,"joystick_output")) {
      rtmSetErrorStatus(P2p2_M,
                        "Error writing mat file header to file joystick.mat");
      return;
    }

    P2p2_DW.ToFile1_IWORK.Count = 0;
    P2p2_DW.ToFile1_IWORK.Decimation = -1;
    P2p2_DW.ToFile1_PWORK.FilePtr = fp;
  }

  /* InitializeConditions for TransferFcn: '<S3>/Pitch: Transfer Fcn' */
  P2p2_X.PitchTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S3>/Elevation: Transfer Fcn' */
  P2p2_X.ElevationTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S3>/Travel: Transfer Fcn' */
  P2p2_X.TravelTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S7>/Integrator' */
  P2p2_X.Integrator_CSTATE = P2p2_P.Integrator_IC;
}

/* Model terminate function */
void P2p2_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: P2p2/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(P2p2_DW.HILInitialize_Card);
    hil_monitor_stop_all(P2p2_DW.HILInitialize_Card);
    is_switching = false;
    if ((P2p2_P.HILInitialize_set_analog_outp_l && !is_switching) ||
        (P2p2_P.HILInitialize_set_analog_outp_h && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &P2p2_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = P2p2_P.HILInitialize_final_analog_outp;
        }
      }

      num_final_analog_outputs = 8U;
    }

    if ((P2p2_P.HILInitialize_set_pwm_outputs_g && !is_switching) ||
        (P2p2_P.HILInitialize_set_pwm_output_c4 && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &P2p2_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = P2p2_P.HILInitialize_final_pwm_outputs;
        }
      }

      num_final_pwm_outputs = 8U;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(P2p2_DW.HILInitialize_Card
                         , P2p2_P.HILInitialize_analog_output_cha,
                         num_final_analog_outputs
                         , P2p2_P.HILInitialize_pwm_channels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &P2p2_DW.HILInitialize_AOVoltages[0]
                         , &P2p2_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(P2p2_DW.HILInitialize_Card,
            P2p2_P.HILInitialize_analog_output_cha, num_final_analog_outputs,
            &P2p2_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(P2p2_DW.HILInitialize_Card,
            P2p2_P.HILInitialize_pwm_channels, num_final_pwm_outputs,
            &P2p2_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(P2p2_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(P2p2_DW.HILInitialize_Card);
    hil_monitor_delete_all(P2p2_DW.HILInitialize_Card);
    hil_close(P2p2_DW.HILInitialize_Card);
    P2p2_DW.HILInitialize_Card = NULL;
  }

  /* Terminate for ToFile: '<Root>/To File' */
  {
    FILE *fp = (FILE *) P2p2_DW.ToFile_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "var.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(P2p2_M, "Error closing MAT-file var.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(P2p2_M, "Error reopening MAT-file var.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 7, P2p2_DW.ToFile_IWORK.Count, "var")) {
        rtmSetErrorStatus(P2p2_M,
                          "Error writing header for var to MAT-file var.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(P2p2_M, "Error closing MAT-file var.mat");
        return;
      }

      P2p2_DW.ToFile_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for S-Function (game_controller_block): '<S4>/Game Controller' */

  /* S-Function Block: P2p2/Joystick/Game Controller (game_controller_block) */
  {
    if (P2p2_P.GameController_Enabled) {
      game_controller_close(P2p2_DW.GameController_Controller);
      P2p2_DW.GameController_Controller = NULL;
    }
  }

  /* Terminate for ToFile: '<Root>/To File1' */
  {
    FILE *fp = (FILE *) P2p2_DW.ToFile1_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "joystick.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(P2p2_M, "Error closing MAT-file joystick.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(P2p2_M, "Error reopening MAT-file joystick.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 3, P2p2_DW.ToFile1_IWORK.Count,
           "joystick_output")) {
        rtmSetErrorStatus(P2p2_M,
                          "Error writing header for joystick_output to MAT-file joystick.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(P2p2_M, "Error closing MAT-file joystick.mat");
        return;
      }

      P2p2_DW.ToFile1_PWORK.FilePtr = (NULL);
    }
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  P2p2_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  P2p2_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  P2p2_initialize();
}

void MdlTerminate(void)
{
  P2p2_terminate();
}

/* Registration function */
RT_MODEL_P2p2_T *P2p2(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  P2p2_P.Integrator_UpperSat = rtInf;
  P2p2_P.Integrator_LowerSat = rtMinusInf;

  /* initialize real-time model */
  (void) memset((void *)P2p2_M, 0,
                sizeof(RT_MODEL_P2p2_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&P2p2_M->solverInfo, &P2p2_M->Timing.simTimeStep);
    rtsiSetTPtr(&P2p2_M->solverInfo, &rtmGetTPtr(P2p2_M));
    rtsiSetStepSizePtr(&P2p2_M->solverInfo, &P2p2_M->Timing.stepSize0);
    rtsiSetdXPtr(&P2p2_M->solverInfo, &P2p2_M->ModelData.derivs);
    rtsiSetContStatesPtr(&P2p2_M->solverInfo, (real_T **)
                         &P2p2_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&P2p2_M->solverInfo, &P2p2_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&P2p2_M->solverInfo, (&rtmGetErrorStatus(P2p2_M)));
    rtsiSetRTModelPtr(&P2p2_M->solverInfo, P2p2_M);
  }

  rtsiSetSimTimeStep(&P2p2_M->solverInfo, MAJOR_TIME_STEP);
  P2p2_M->ModelData.intgData.f[0] = P2p2_M->ModelData.odeF[0];
  P2p2_M->ModelData.contStates = ((real_T *) &P2p2_X);
  rtsiSetSolverData(&P2p2_M->solverInfo, (void *)&P2p2_M->ModelData.intgData);
  rtsiSetSolverName(&P2p2_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = P2p2_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    P2p2_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    P2p2_M->Timing.sampleTimes = (&P2p2_M->Timing.sampleTimesArray[0]);
    P2p2_M->Timing.offsetTimes = (&P2p2_M->Timing.offsetTimesArray[0]);

    /* task periods */
    P2p2_M->Timing.sampleTimes[0] = (0.0);
    P2p2_M->Timing.sampleTimes[1] = (0.01);

    /* task offsets */
    P2p2_M->Timing.offsetTimes[0] = (0.0);
    P2p2_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(P2p2_M, &P2p2_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = P2p2_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    P2p2_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(P2p2_M, -1);
  P2p2_M->Timing.stepSize0 = 0.01;
  P2p2_M->Timing.stepSize1 = 0.01;

  /* External mode info */
  P2p2_M->Sizes.checksums[0] = (906022945U);
  P2p2_M->Sizes.checksums[1] = (3053244993U);
  P2p2_M->Sizes.checksums[2] = (1918010593U);
  P2p2_M->Sizes.checksums[3] = (827604092U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    P2p2_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(P2p2_M->extModeInfo,
      &P2p2_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(P2p2_M->extModeInfo, P2p2_M->Sizes.checksums);
    rteiSetTPtr(P2p2_M->extModeInfo, rtmGetTPtr(P2p2_M));
  }

  P2p2_M->solverInfoPtr = (&P2p2_M->solverInfo);
  P2p2_M->Timing.stepSize = (0.01);
  rtsiSetFixedStepSize(&P2p2_M->solverInfo, 0.01);
  rtsiSetSolverMode(&P2p2_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  P2p2_M->ModelData.blockIO = ((void *) &P2p2_B);

  {
    P2p2_B.PitchCounttorad = 0.0;
    P2p2_B.DegtoRad = 0.0;
    P2p2_B.DegtoRad_o = 0.0;
    P2p2_B.ElevationCounttorad = 0.0;
    P2p2_B.DegtoRad_oh = 0.0;
    P2p2_B.DegtoRad_i = 0.0;
    P2p2_B.TravelCounttorad = 0.0;
    P2p2_B.DegtoRad_l = 0.0;
    P2p2_B.DegtoRad_j = 0.0;
    P2p2_B.Joystick_gain_x = 0.0;
    P2p2_B.Joystick_gain_y = 0.0;
    P2p2_B.Gain1 = 0.0;
    P2p2_B.K_ep = 0.0;
    P2p2_B.K_ei = 0.0;
    P2p2_B.FrontmotorSaturation = 0.0;
    P2p2_B.BackmotorSaturation = 0.0;
  }

  /* parameters */
  P2p2_M->ModelData.defaultParam = ((real_T *)&P2p2_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &P2p2_X;
    P2p2_M->ModelData.contStates = (x);
    (void) memset((void *)&P2p2_X, 0,
                  sizeof(X_P2p2_T));
  }

  /* states (dwork) */
  P2p2_M->ModelData.dwork = ((void *) &P2p2_DW);
  (void) memset((void *)&P2p2_DW, 0,
                sizeof(DW_P2p2_T));

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      P2p2_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      P2p2_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      P2p2_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      P2p2_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      P2p2_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      P2p2_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      P2p2_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      P2p2_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  P2p2_DW.HILWriteAnalog_Buffer[0] = 0.0;
  P2p2_DW.HILWriteAnalog_Buffer[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    P2p2_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 17;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  /* Initialize Sizes */
  P2p2_M->Sizes.numContStates = (4);   /* Number of continuous states */
  P2p2_M->Sizes.numY = (0);            /* Number of model outputs */
  P2p2_M->Sizes.numU = (0);            /* Number of model inputs */
  P2p2_M->Sizes.sysDirFeedThru = (0);  /* The model is not direct feedthrough */
  P2p2_M->Sizes.numSampTimes = (2);    /* Number of sample times */
  P2p2_M->Sizes.numBlocks = (64);      /* Number of blocks */
  P2p2_M->Sizes.numBlockIO = (16);     /* Number of block outputs */
  P2p2_M->Sizes.numBlockPrms = (159);  /* Sum of parameter "widths" */
  return P2p2_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
