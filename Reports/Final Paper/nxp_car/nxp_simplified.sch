<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="9.5.1">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="2" name="Route2" color="16" fill="1" visible="no" active="no"/>
<layer number="3" name="Route3" color="17" fill="1" visible="no" active="no"/>
<layer number="4" name="Route4" color="18" fill="1" visible="no" active="no"/>
<layer number="5" name="Route5" color="19" fill="1" visible="no" active="no"/>
<layer number="6" name="Route6" color="25" fill="1" visible="no" active="no"/>
<layer number="7" name="Route7" color="26" fill="1" visible="no" active="no"/>
<layer number="8" name="Route8" color="27" fill="1" visible="no" active="no"/>
<layer number="9" name="Route9" color="28" fill="1" visible="no" active="no"/>
<layer number="10" name="Route10" color="29" fill="1" visible="no" active="no"/>
<layer number="11" name="Route11" color="30" fill="1" visible="no" active="no"/>
<layer number="12" name="Route12" color="20" fill="1" visible="no" active="no"/>
<layer number="13" name="Route13" color="21" fill="1" visible="no" active="no"/>
<layer number="14" name="Route14" color="22" fill="1" visible="no" active="no"/>
<layer number="15" name="Route15" color="23" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="24" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="88" name="SimResults" color="9" fill="1" visible="yes" active="yes"/>
<layer number="89" name="SimProbes" color="9" fill="1" visible="yes" active="yes"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="CMPE-460-NXPCUP">
<packages>
<package name="K64F">
<smd name="P$1" x="-10.16" y="5.08" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$2" x="-2.54" y="5.08" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$3" x="5.08" y="5.08" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$4" x="12.7" y="5.08" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$5" x="-10.16" y="-2.54" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$6" x="-3.81" y="-2.54" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$7" x="2.54" y="-2.54" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$8" x="7.62" y="-2.54" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$9" x="16.51" y="-2.54" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$10" x="-10.16" y="-7.62" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$11" x="-3.81" y="-7.62" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$12" x="5.08" y="-6.35" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$13" x="10.16" y="-6.35" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$14" x="12.7" y="-6.35" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$15" x="12.7" y="-2.54" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$16" x="11.43" y="1.27" dx="1.27" dy="0.635" layer="1"/>
</package>
<package name="RPI_MOTOR_SHEILD">
<smd name="P$1" x="-16.51" y="8.89" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$2" x="-8.89" y="8.89" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$3" x="-3.81" y="8.89" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$4" x="1.27" y="8.89" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$5" x="8.89" y="7.62" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$6" x="16.51" y="7.62" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$7" x="12.7" y="2.54" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$8" x="7.62" y="2.54" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$9" x="-8.89" y="2.54" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$10" x="-16.51" y="1.27" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$11" x="-15.24" y="-2.54" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$12" x="0" y="-2.54" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$13" x="11.43" y="-3.81" dx="1.27" dy="0.635" layer="1"/>
</package>
<package name="K64F_ADAPTER">
<smd name="P$1" x="-25.4" y="6.35" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$2" x="-19.05" y="6.35" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$3" x="-13.97" y="6.35" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$4" x="-7.62" y="6.35" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$5" x="-1.27" y="6.35" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$6" x="5.08" y="6.35" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$7" x="11.43" y="6.35" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$8" x="20.32" y="6.35" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$9" x="-25.4" y="-1.27" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$10" x="-21.59" y="0" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$11" x="-16.51" y="0" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$12" x="-10.16" y="-1.27" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$13" x="-5.08" y="-1.27" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$14" x="2.54" y="-1.27" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$15" x="8.89" y="-1.27" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$16" x="16.51" y="-1.27" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$17" x="21.59" y="-1.27" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$18" x="-24.13" y="-7.62" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$19" x="-17.78" y="-7.62" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$20" x="-12.7" y="-7.62" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$21" x="-6.35" y="-7.62" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$22" x="-1.27" y="-7.62" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$23" x="6.35" y="-7.62" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$24" x="12.7" y="-5.08" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$25" x="2.54" y="-5.08" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$26" x="-1.27" y="0" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$27" x="12.7" y="-3.81" dx="1.27" dy="0.635" layer="1"/>
</package>
</packages>
<symbols>
<symbol name="K64F">
<pin name="3.3V" x="17.78" y="27.94" length="middle" rot="R180"/>
<pin name="GND" x="17.78" y="22.86" length="middle" rot="R180"/>
<pin name="UART3_RX" x="17.78" y="17.78" length="middle" rot="R180"/>
<pin name="UART3_TX" x="17.78" y="12.7" length="middle" rot="R180"/>
<pin name="MOTOR2_B" x="17.78" y="7.62" length="middle" rot="R180"/>
<pin name="MOTOR2_A" x="17.78" y="2.54" length="middle" rot="R180"/>
<pin name="MOTOR1_B" x="17.78" y="-2.54" length="middle" rot="R180"/>
<pin name="MOTOR1_A" x="17.78" y="-7.62" length="middle" rot="R180"/>
<pin name="SERVO_PWM" x="17.78" y="-12.7" length="middle" rot="R180"/>
<pin name="CMR_CLK" x="17.78" y="-17.78" length="middle" rot="R180"/>
<pin name="CMR_SI" x="17.78" y="-22.86" length="middle" rot="R180"/>
<pin name="CMR_AO" x="17.78" y="-27.94" length="middle" rot="R180"/>
<wire x1="12.7" y1="30.48" x2="12.7" y2="-33.02" width="0.254" layer="94"/>
<wire x1="12.7" y1="-33.02" x2="-12.7" y2="-33.02" width="0.254" layer="94"/>
<wire x1="-12.7" y1="-33.02" x2="-12.7" y2="30.48" width="0.254" layer="94"/>
<wire x1="-12.7" y1="30.48" x2="12.7" y2="30.48" width="0.254" layer="94"/>
<text x="-12.7" y="33.02" size="1.778" layer="95">&gt;NAME</text>
<text x="-12.7" y="-35.56" size="1.778" layer="95">&gt;VALUE</text>
</symbol>
<symbol name="RPI_MOTOR_SHEILD">
<pin name="BATT+" x="2.54" y="22.86" length="middle" rot="R270"/>
<pin name="BATT-" x="-2.54" y="22.86" length="middle" rot="R270"/>
<pin name="5V_OUT" x="-5.08" y="-22.86" length="middle" rot="R90"/>
<pin name="3.3V_OUT" x="0" y="-22.86" length="middle" rot="R90"/>
<pin name="GND" x="5.08" y="-22.86" length="middle" rot="R90"/>
<pin name="MOTOR2_B_IN" x="-27.94" y="7.62" length="middle"/>
<pin name="MOTOR2_A_IN" x="-27.94" y="2.54" length="middle"/>
<pin name="MOTOR1_B_IN" x="-27.94" y="-2.54" length="middle"/>
<pin name="MOTOR1_A_IN" x="-27.94" y="-7.62" length="middle"/>
<pin name="MOTOR2_B_OUT" x="27.94" y="7.62" length="middle" rot="R180"/>
<pin name="MOTOR2_A_OUT" x="27.94" y="2.54" length="middle" rot="R180"/>
<pin name="MOTOR1_B_OUT" x="27.94" y="-2.54" length="middle" rot="R180"/>
<pin name="MOTOR1_A_OUT" x="27.94" y="-7.62" length="middle" rot="R180"/>
<wire x1="-22.86" y1="-17.78" x2="-22.86" y2="17.78" width="0.254" layer="94"/>
<wire x1="-22.86" y1="17.78" x2="22.86" y2="17.78" width="0.254" layer="94"/>
<wire x1="22.86" y1="17.78" x2="22.86" y2="-17.78" width="0.254" layer="94"/>
<wire x1="22.86" y1="-17.78" x2="-22.86" y2="-17.78" width="0.254" layer="94"/>
<text x="-22.86" y="20.32" size="1.778" layer="95">&gt;NAME</text>
<text x="10.16" y="-20.32" size="1.778" layer="95">&gt;VALUE</text>
</symbol>
<symbol name="K64F_ADAPTER">
<pin name="3.3V_OUT" x="-25.4" y="27.94" length="middle"/>
<pin name="K64F_GND" x="-25.4" y="22.86" length="middle"/>
<pin name="UART_TX" x="-25.4" y="17.78" length="middle"/>
<pin name="UART_RX" x="-25.4" y="12.7" length="middle"/>
<pin name="MOTOR_2B_IN" x="-25.4" y="7.62" length="middle"/>
<pin name="MOTOR_2A_IN" x="-25.4" y="2.54" length="middle"/>
<pin name="MOTOR_1B_IN" x="-25.4" y="-2.54" length="middle"/>
<pin name="MOTOR_1A_IN" x="-25.4" y="-7.62" length="middle"/>
<pin name="SERVO_PWM" x="-25.4" y="-12.7" length="middle"/>
<pin name="CMR_CLK" x="-25.4" y="-17.78" length="middle"/>
<pin name="CMR_SI" x="-25.4" y="-22.86" length="middle"/>
<pin name="CMR_AO_OUT" x="-25.4" y="-27.94" length="middle"/>
<pin name="GND" x="-5.08" y="-43.18" length="middle" rot="R90"/>
<pin name="3.3V" x="0" y="-43.18" length="middle" rot="R90"/>
<pin name="5V" x="5.08" y="-43.18" length="middle" rot="R90"/>
<pin name="SERVO_PWM_OUT" x="25.4" y="27.94" length="middle" rot="R180"/>
<pin name="SERVO_5V" x="25.4" y="22.86" length="middle" rot="R180"/>
<pin name="SERVO_GND" x="25.4" y="17.78" length="middle" rot="R180"/>
<pin name="CMR_5V" x="25.4" y="12.7" length="middle" rot="R180"/>
<pin name="CMR_GND" x="25.4" y="7.62" length="middle" rot="R180"/>
<pin name="CMR_CLK_OUT" x="25.4" y="2.54" length="middle" rot="R180"/>
<pin name="CMR_SI_OUT" x="25.4" y="-2.54" length="middle" rot="R180"/>
<pin name="CMR_AO_IN" x="25.4" y="-7.62" length="middle" rot="R180"/>
<wire x1="-20.32" y1="33.02" x2="-20.32" y2="-38.1" width="0.254" layer="94"/>
<wire x1="-20.32" y1="-38.1" x2="20.32" y2="-38.1" width="0.254" layer="94"/>
<wire x1="20.32" y1="-38.1" x2="20.32" y2="33.02" width="0.254" layer="94"/>
<wire x1="20.32" y1="33.02" x2="-20.32" y2="33.02" width="0.254" layer="94"/>
<text x="-17.78" y="35.56" size="1.778" layer="95">&gt;NAME</text>
<text x="10.16" y="-40.64" size="1.778" layer="95">&gt;VALUE</text>
<pin name="MOTOR2_B_OUT" x="25.4" y="-12.7" length="middle" rot="R180"/>
<pin name="MOTOR_2A_OUT" x="25.4" y="-17.78" length="middle" rot="R180"/>
<pin name="MOTOR_1B_OUT" x="25.4" y="-22.86" length="middle" rot="R180"/>
<pin name="MOTOR_1A_OUT" x="25.4" y="-27.94" length="middle" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="K64F">
<gates>
<gate name="G$1" symbol="K64F" x="0" y="0"/>
</gates>
<devices>
<device name="" package="K64F">
<connects>
<connect gate="G$1" pin="3.3V" pad="P$1"/>
<connect gate="G$1" pin="CMR_AO" pad="P$2"/>
<connect gate="G$1" pin="CMR_CLK" pad="P$3"/>
<connect gate="G$1" pin="CMR_SI" pad="P$4"/>
<connect gate="G$1" pin="GND" pad="P$5"/>
<connect gate="G$1" pin="MOTOR1_A" pad="P$6"/>
<connect gate="G$1" pin="MOTOR1_B" pad="P$7"/>
<connect gate="G$1" pin="MOTOR2_A" pad="P$8"/>
<connect gate="G$1" pin="MOTOR2_B" pad="P$9"/>
<connect gate="G$1" pin="SERVO_PWM" pad="P$10"/>
<connect gate="G$1" pin="UART3_RX" pad="P$11"/>
<connect gate="G$1" pin="UART3_TX" pad="P$12"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="RPI_MOTOR_SHEILD">
<gates>
<gate name="G$1" symbol="RPI_MOTOR_SHEILD" x="0" y="0"/>
</gates>
<devices>
<device name="" package="RPI_MOTOR_SHEILD">
<connects>
<connect gate="G$1" pin="3.3V_OUT" pad="P$1"/>
<connect gate="G$1" pin="5V_OUT" pad="P$2"/>
<connect gate="G$1" pin="BATT+" pad="P$3"/>
<connect gate="G$1" pin="BATT-" pad="P$4"/>
<connect gate="G$1" pin="GND" pad="P$5"/>
<connect gate="G$1" pin="MOTOR1_A_IN" pad="P$6"/>
<connect gate="G$1" pin="MOTOR1_A_OUT" pad="P$7"/>
<connect gate="G$1" pin="MOTOR1_B_IN" pad="P$8"/>
<connect gate="G$1" pin="MOTOR1_B_OUT" pad="P$9"/>
<connect gate="G$1" pin="MOTOR2_A_IN" pad="P$10"/>
<connect gate="G$1" pin="MOTOR2_A_OUT" pad="P$11"/>
<connect gate="G$1" pin="MOTOR2_B_IN" pad="P$12"/>
<connect gate="G$1" pin="MOTOR2_B_OUT" pad="P$13"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="K64F_ADAPTER">
<gates>
<gate name="G$1" symbol="K64F_ADAPTER" x="0" y="0"/>
</gates>
<devices>
<device name="" package="K64F_ADAPTER">
<connects>
<connect gate="G$1" pin="3.3V" pad="P$3"/>
<connect gate="G$1" pin="3.3V_OUT" pad="P$2"/>
<connect gate="G$1" pin="5V" pad="P$1"/>
<connect gate="G$1" pin="CMR_5V" pad="P$4"/>
<connect gate="G$1" pin="CMR_AO_IN" pad="P$5"/>
<connect gate="G$1" pin="CMR_AO_OUT" pad="P$6"/>
<connect gate="G$1" pin="CMR_CLK" pad="P$7"/>
<connect gate="G$1" pin="CMR_CLK_OUT" pad="P$8"/>
<connect gate="G$1" pin="CMR_GND" pad="P$9"/>
<connect gate="G$1" pin="CMR_SI" pad="P$10"/>
<connect gate="G$1" pin="CMR_SI_OUT" pad="P$11"/>
<connect gate="G$1" pin="GND" pad="P$12"/>
<connect gate="G$1" pin="K64F_GND" pad="P$13"/>
<connect gate="G$1" pin="MOTOR2_B_OUT" pad="P$24"/>
<connect gate="G$1" pin="MOTOR_1A_IN" pad="P$14"/>
<connect gate="G$1" pin="MOTOR_1A_OUT" pad="P$25"/>
<connect gate="G$1" pin="MOTOR_1B_IN" pad="P$15"/>
<connect gate="G$1" pin="MOTOR_1B_OUT" pad="P$26"/>
<connect gate="G$1" pin="MOTOR_2A_IN" pad="P$17"/>
<connect gate="G$1" pin="MOTOR_2A_OUT" pad="P$27"/>
<connect gate="G$1" pin="MOTOR_2B_IN" pad="P$16"/>
<connect gate="G$1" pin="SERVO_5V" pad="P$18"/>
<connect gate="G$1" pin="SERVO_GND" pad="P$19"/>
<connect gate="G$1" pin="SERVO_PWM" pad="P$20"/>
<connect gate="G$1" pin="SERVO_PWM_OUT" pad="P$21"/>
<connect gate="G$1" pin="UART_RX" pad="P$22"/>
<connect gate="G$1" pin="UART_TX" pad="P$23"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="_" library="CMPE-460-NXPCUP" deviceset="K64F" device=""/>
<part name="___" library="CMPE-460-NXPCUP" deviceset="RPI_MOTOR_SHEILD" device=""/>
<part name="U$1" library="CMPE-460-NXPCUP" deviceset="K64F_ADAPTER" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="_" gate="G$1" x="22.86" y="50.8" smashed="yes">
<attribute name="NAME" x="10.16" y="83.82" size="1.778" layer="95"/>
<attribute name="VALUE" x="10.16" y="15.24" size="1.778" layer="95"/>
</instance>
<instance part="___" gate="G$1" x="190.5" y="30.48" smashed="yes">
<attribute name="NAME" x="167.64" y="48.26" size="1.778" layer="95"/>
<attribute name="VALUE" x="167.64" y="2.54" size="1.778" layer="95"/>
</instance>
<instance part="U$1" gate="G$1" x="106.68" y="50.8" smashed="yes">
<attribute name="NAME" x="88.9" y="86.36" size="1.778" layer="95"/>
<attribute name="VALUE" x="116.84" y="10.16" size="1.778" layer="95"/>
</instance>
</instances>
<busses>
</busses>
<nets>
<net name="N$1" class="0">
<segment>
<pinref part="_" gate="G$1" pin="3.3V"/>
<wire x1="40.64" y1="78.74" x2="81.28" y2="78.74" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="3.3V_OUT"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<pinref part="_" gate="G$1" pin="GND"/>
<wire x1="40.64" y1="73.66" x2="81.28" y2="73.66" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="K64F_GND"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<pinref part="_" gate="G$1" pin="UART3_RX"/>
<wire x1="40.64" y1="68.58" x2="81.28" y2="68.58" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="UART_TX"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="_" gate="G$1" pin="UART3_TX"/>
<wire x1="40.64" y1="63.5" x2="81.28" y2="63.5" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="UART_RX"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<pinref part="_" gate="G$1" pin="MOTOR2_B"/>
<wire x1="40.64" y1="58.42" x2="81.28" y2="58.42" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="MOTOR_2B_IN"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<pinref part="_" gate="G$1" pin="MOTOR2_A"/>
<wire x1="40.64" y1="53.34" x2="81.28" y2="53.34" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="MOTOR_2A_IN"/>
</segment>
</net>
<net name="N$7" class="0">
<segment>
<pinref part="_" gate="G$1" pin="MOTOR1_B"/>
<wire x1="40.64" y1="48.26" x2="81.28" y2="48.26" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="MOTOR_1B_IN"/>
</segment>
</net>
<net name="N$8" class="0">
<segment>
<pinref part="_" gate="G$1" pin="MOTOR1_A"/>
<wire x1="40.64" y1="43.18" x2="81.28" y2="43.18" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="MOTOR_1A_IN"/>
</segment>
</net>
<net name="N$9" class="0">
<segment>
<pinref part="_" gate="G$1" pin="SERVO_PWM"/>
<wire x1="40.64" y1="38.1" x2="81.28" y2="38.1" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="SERVO_PWM"/>
</segment>
</net>
<net name="N$10" class="0">
<segment>
<pinref part="_" gate="G$1" pin="CMR_CLK"/>
<wire x1="40.64" y1="33.02" x2="81.28" y2="33.02" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="CMR_CLK"/>
</segment>
</net>
<net name="N$11" class="0">
<segment>
<pinref part="_" gate="G$1" pin="CMR_SI"/>
<wire x1="40.64" y1="27.94" x2="81.28" y2="27.94" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="CMR_SI"/>
</segment>
</net>
<net name="N$12" class="0">
<segment>
<pinref part="_" gate="G$1" pin="CMR_AO"/>
<wire x1="40.64" y1="22.86" x2="81.28" y2="22.86" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="CMR_AO_OUT"/>
</segment>
</net>
<net name="N$13" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="GND"/>
<wire x1="101.6" y1="7.62" x2="101.6" y2="-10.16" width="0.1524" layer="91"/>
<wire x1="101.6" y1="-10.16" x2="195.58" y2="-10.16" width="0.1524" layer="91"/>
<pinref part="___" gate="G$1" pin="GND"/>
<wire x1="195.58" y1="-10.16" x2="195.58" y2="7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$14" class="0">
<segment>
<pinref part="___" gate="G$1" pin="3.3V_OUT"/>
<wire x1="190.5" y1="7.62" x2="190.5" y2="-5.08" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="3.3V"/>
<wire x1="190.5" y1="-5.08" x2="106.68" y2="-5.08" width="0.1524" layer="91"/>
<wire x1="106.68" y1="-5.08" x2="106.68" y2="7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$15" class="0">
<segment>
<pinref part="___" gate="G$1" pin="5V_OUT"/>
<wire x1="185.42" y1="7.62" x2="185.42" y2="-2.54" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="5V"/>
<wire x1="185.42" y1="-2.54" x2="111.76" y2="-2.54" width="0.1524" layer="91"/>
<wire x1="111.76" y1="-2.54" x2="111.76" y2="7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$16" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="MOTOR_1A_OUT"/>
<pinref part="___" gate="G$1" pin="MOTOR1_A_IN"/>
<wire x1="132.08" y1="22.86" x2="162.56" y2="22.86" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$17" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="MOTOR_1B_OUT"/>
<pinref part="___" gate="G$1" pin="MOTOR1_B_IN"/>
<wire x1="132.08" y1="27.94" x2="162.56" y2="27.94" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$18" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="MOTOR_2A_OUT"/>
<pinref part="___" gate="G$1" pin="MOTOR2_A_IN"/>
<wire x1="132.08" y1="33.02" x2="162.56" y2="33.02" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$19" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="MOTOR2_B_OUT"/>
<pinref part="___" gate="G$1" pin="MOTOR2_B_IN"/>
<wire x1="132.08" y1="38.1" x2="162.56" y2="38.1" width="0.1524" layer="91"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
