#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/TiOsa-maze.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/TiOsa-maze.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1360933422/osa.o ${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1472/Timer0.o ${OBJECTDIR}/_ext/1472/Quadrature.o ${OBJECTDIR}/_ext/760475324/xlcd.o ${OBJECTDIR}/_ext/760475324/xlcddelay.o ${OBJECTDIR}/_ext/1360934519/pwm.o ${OBJECTDIR}/_ext/2102461962/usart.o ${OBJECTDIR}/_ext/1472/myadc.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1360933422/osa.o.d ${OBJECTDIR}/_ext/1472/main.o.d ${OBJECTDIR}/_ext/1472/Timer0.o.d ${OBJECTDIR}/_ext/1472/Quadrature.o.d ${OBJECTDIR}/_ext/760475324/xlcd.o.d ${OBJECTDIR}/_ext/760475324/xlcddelay.o.d ${OBJECTDIR}/_ext/1360934519/pwm.o.d ${OBJECTDIR}/_ext/2102461962/usart.o.d ${OBJECTDIR}/_ext/1472/myadc.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1360933422/osa.o ${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1472/Timer0.o ${OBJECTDIR}/_ext/1472/Quadrature.o ${OBJECTDIR}/_ext/760475324/xlcd.o ${OBJECTDIR}/_ext/760475324/xlcddelay.o ${OBJECTDIR}/_ext/1360934519/pwm.o ${OBJECTDIR}/_ext/2102461962/usart.o ${OBJECTDIR}/_ext/1472/myadc.o


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/TiOsa-maze.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F4550
MP_PROCESSOR_OPTION_LD=18f4550
MP_LINKER_DEBUG_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1360933422/osa.o: ../osa/osa.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360933422 
	@${RM} ${OBJECTDIR}/_ext/1360933422/osa.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -I"../../../../../../../Program Files (x86)/Microchip/mplabc18/v3.37.01/h" -I"../osa" -I".." -I"../xlcd" -I"../pwm" -I"../osa/kernel/events" -I"../osa/kernel/timers" -I"../osa/port" -I"../osa/kernel" -I"../osa/port/pic18" -I"../osa/kernel/system" -I"../usart" -ms -oa- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1360933422/osa.o   ../osa/osa.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1360933422/osa.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360933422/osa.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -I"../../../../../../../Program Files (x86)/Microchip/mplabc18/v3.37.01/h" -I"../osa" -I".." -I"../xlcd" -I"../pwm" -I"../osa/kernel/events" -I"../osa/kernel/timers" -I"../osa/port" -I"../osa/kernel" -I"../osa/port/pic18" -I"../osa/kernel/system" -I"../usart" -ms -oa- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/main.o   ../main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1472/Timer0.o: ../Timer0.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/Timer0.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -I"../../../../../../../Program Files (x86)/Microchip/mplabc18/v3.37.01/h" -I"../osa" -I".." -I"../xlcd" -I"../pwm" -I"../osa/kernel/events" -I"../osa/kernel/timers" -I"../osa/port" -I"../osa/kernel" -I"../osa/port/pic18" -I"../osa/kernel/system" -I"../usart" -ms -oa- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/Timer0.o   ../Timer0.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/Timer0.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Timer0.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1472/Quadrature.o: ../Quadrature.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/Quadrature.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -I"../../../../../../../Program Files (x86)/Microchip/mplabc18/v3.37.01/h" -I"../osa" -I".." -I"../xlcd" -I"../pwm" -I"../osa/kernel/events" -I"../osa/kernel/timers" -I"../osa/port" -I"../osa/kernel" -I"../osa/port/pic18" -I"../osa/kernel/system" -I"../usart" -ms -oa- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/Quadrature.o   ../Quadrature.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/Quadrature.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Quadrature.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760475324/xlcd.o: ../xlcd/xlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/760475324 
	@${RM} ${OBJECTDIR}/_ext/760475324/xlcd.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -I"../../../../../../../Program Files (x86)/Microchip/mplabc18/v3.37.01/h" -I"../osa" -I".." -I"../xlcd" -I"../pwm" -I"../osa/kernel/events" -I"../osa/kernel/timers" -I"../osa/port" -I"../osa/kernel" -I"../osa/port/pic18" -I"../osa/kernel/system" -I"../usart" -ms -oa- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/760475324/xlcd.o   ../xlcd/xlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760475324/xlcd.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760475324/xlcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760475324/xlcddelay.o: ../xlcd/xlcddelay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/760475324 
	@${RM} ${OBJECTDIR}/_ext/760475324/xlcddelay.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -I"../../../../../../../Program Files (x86)/Microchip/mplabc18/v3.37.01/h" -I"../osa" -I".." -I"../xlcd" -I"../pwm" -I"../osa/kernel/events" -I"../osa/kernel/timers" -I"../osa/port" -I"../osa/kernel" -I"../osa/port/pic18" -I"../osa/kernel/system" -I"../usart" -ms -oa- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/760475324/xlcddelay.o   ../xlcd/xlcddelay.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760475324/xlcddelay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760475324/xlcddelay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1360934519/pwm.o: ../pwm/pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360934519 
	@${RM} ${OBJECTDIR}/_ext/1360934519/pwm.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -I"../../../../../../../Program Files (x86)/Microchip/mplabc18/v3.37.01/h" -I"../osa" -I".." -I"../xlcd" -I"../pwm" -I"../osa/kernel/events" -I"../osa/kernel/timers" -I"../osa/port" -I"../osa/kernel" -I"../osa/port/pic18" -I"../osa/kernel/system" -I"../usart" -ms -oa- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1360934519/pwm.o   ../pwm/pwm.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1360934519/pwm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360934519/pwm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/2102461962/usart.o: ../usart/usart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2102461962 
	@${RM} ${OBJECTDIR}/_ext/2102461962/usart.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -I"../../../../../../../Program Files (x86)/Microchip/mplabc18/v3.37.01/h" -I"../osa" -I".." -I"../xlcd" -I"../pwm" -I"../osa/kernel/events" -I"../osa/kernel/timers" -I"../osa/port" -I"../osa/kernel" -I"../osa/port/pic18" -I"../osa/kernel/system" -I"../usart" -ms -oa- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/2102461962/usart.o   ../usart/usart.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/2102461962/usart.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2102461962/usart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1472/myadc.o: ../myadc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/myadc.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -I"../../../../../../../Program Files (x86)/Microchip/mplabc18/v3.37.01/h" -I"../osa" -I".." -I"../xlcd" -I"../pwm" -I"../osa/kernel/events" -I"../osa/kernel/timers" -I"../osa/port" -I"../osa/kernel" -I"../osa/port/pic18" -I"../osa/kernel/system" -I"../usart" -ms -oa- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/myadc.o   ../myadc.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/myadc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/myadc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
else
${OBJECTDIR}/_ext/1360933422/osa.o: ../osa/osa.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360933422 
	@${RM} ${OBJECTDIR}/_ext/1360933422/osa.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"../../../../../../../Program Files (x86)/Microchip/mplabc18/v3.37.01/h" -I"../osa" -I".." -I"../xlcd" -I"../pwm" -I"../osa/kernel/events" -I"../osa/kernel/timers" -I"../osa/port" -I"../osa/kernel" -I"../osa/port/pic18" -I"../osa/kernel/system" -I"../usart" -ms -oa- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1360933422/osa.o   ../osa/osa.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1360933422/osa.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360933422/osa.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"../../../../../../../Program Files (x86)/Microchip/mplabc18/v3.37.01/h" -I"../osa" -I".." -I"../xlcd" -I"../pwm" -I"../osa/kernel/events" -I"../osa/kernel/timers" -I"../osa/port" -I"../osa/kernel" -I"../osa/port/pic18" -I"../osa/kernel/system" -I"../usart" -ms -oa- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/main.o   ../main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1472/Timer0.o: ../Timer0.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/Timer0.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"../../../../../../../Program Files (x86)/Microchip/mplabc18/v3.37.01/h" -I"../osa" -I".." -I"../xlcd" -I"../pwm" -I"../osa/kernel/events" -I"../osa/kernel/timers" -I"../osa/port" -I"../osa/kernel" -I"../osa/port/pic18" -I"../osa/kernel/system" -I"../usart" -ms -oa- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/Timer0.o   ../Timer0.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/Timer0.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Timer0.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1472/Quadrature.o: ../Quadrature.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/Quadrature.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"../../../../../../../Program Files (x86)/Microchip/mplabc18/v3.37.01/h" -I"../osa" -I".." -I"../xlcd" -I"../pwm" -I"../osa/kernel/events" -I"../osa/kernel/timers" -I"../osa/port" -I"../osa/kernel" -I"../osa/port/pic18" -I"../osa/kernel/system" -I"../usart" -ms -oa- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/Quadrature.o   ../Quadrature.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/Quadrature.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Quadrature.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760475324/xlcd.o: ../xlcd/xlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/760475324 
	@${RM} ${OBJECTDIR}/_ext/760475324/xlcd.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"../../../../../../../Program Files (x86)/Microchip/mplabc18/v3.37.01/h" -I"../osa" -I".." -I"../xlcd" -I"../pwm" -I"../osa/kernel/events" -I"../osa/kernel/timers" -I"../osa/port" -I"../osa/kernel" -I"../osa/port/pic18" -I"../osa/kernel/system" -I"../usart" -ms -oa- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/760475324/xlcd.o   ../xlcd/xlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760475324/xlcd.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760475324/xlcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760475324/xlcddelay.o: ../xlcd/xlcddelay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/760475324 
	@${RM} ${OBJECTDIR}/_ext/760475324/xlcddelay.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"../../../../../../../Program Files (x86)/Microchip/mplabc18/v3.37.01/h" -I"../osa" -I".." -I"../xlcd" -I"../pwm" -I"../osa/kernel/events" -I"../osa/kernel/timers" -I"../osa/port" -I"../osa/kernel" -I"../osa/port/pic18" -I"../osa/kernel/system" -I"../usart" -ms -oa- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/760475324/xlcddelay.o   ../xlcd/xlcddelay.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760475324/xlcddelay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760475324/xlcddelay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1360934519/pwm.o: ../pwm/pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360934519 
	@${RM} ${OBJECTDIR}/_ext/1360934519/pwm.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"../../../../../../../Program Files (x86)/Microchip/mplabc18/v3.37.01/h" -I"../osa" -I".." -I"../xlcd" -I"../pwm" -I"../osa/kernel/events" -I"../osa/kernel/timers" -I"../osa/port" -I"../osa/kernel" -I"../osa/port/pic18" -I"../osa/kernel/system" -I"../usart" -ms -oa- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1360934519/pwm.o   ../pwm/pwm.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1360934519/pwm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360934519/pwm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/2102461962/usart.o: ../usart/usart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2102461962 
	@${RM} ${OBJECTDIR}/_ext/2102461962/usart.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"../../../../../../../Program Files (x86)/Microchip/mplabc18/v3.37.01/h" -I"../osa" -I".." -I"../xlcd" -I"../pwm" -I"../osa/kernel/events" -I"../osa/kernel/timers" -I"../osa/port" -I"../osa/kernel" -I"../osa/port/pic18" -I"../osa/kernel/system" -I"../usart" -ms -oa- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/2102461962/usart.o   ../usart/usart.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/2102461962/usart.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2102461962/usart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1472/myadc.o: ../myadc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/myadc.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"../../../../../../../Program Files (x86)/Microchip/mplabc18/v3.37.01/h" -I"../osa" -I".." -I"../xlcd" -I"../pwm" -I"../osa/kernel/events" -I"../osa/kernel/timers" -I"../osa/port" -I"../osa/kernel" -I"../osa/port/pic18" -I"../osa/kernel/system" -I"../usart" -ms -oa- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/myadc.o   ../myadc.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/myadc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/myadc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/TiOsa-maze.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../rm18f4550\ -\ HID\ Bootload.lkr
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE) "..\rm18f4550 - HID Bootload.lkr"  -p$(MP_PROCESSOR_OPTION_LD)  -w -x -u_DEBUG -m"$(BINDIR_)$(TARGETBASE).map" -w -l"../../../../../../../Program Files (x86)/Microchip/mplabc18/v3.37.01/lib" -l"../../../../../../../Program Files/Microchip/mplabc18/v3.37.01/lib"  -z__MPLAB_BUILD=1  -u_CRUNTIME -z__MPLAB_DEBUG=1 $(MP_LINKER_DEBUG_OPTION) -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/TiOsa-maze.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
else
dist/${CND_CONF}/${IMAGE_TYPE}/TiOsa-maze.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../rm18f4550\ -\ HID\ Bootload.lkr
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE) "..\rm18f4550 - HID Bootload.lkr"  -p$(MP_PROCESSOR_OPTION_LD)  -w  -m"$(BINDIR_)$(TARGETBASE).map" -w -l"../../../../../../../Program Files (x86)/Microchip/mplabc18/v3.37.01/lib" -l"../../../../../../../Program Files/Microchip/mplabc18/v3.37.01/lib"  -z__MPLAB_BUILD=1  -u_CRUNTIME -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/TiOsa-maze.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
