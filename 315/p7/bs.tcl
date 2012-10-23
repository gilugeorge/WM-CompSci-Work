#bs.tcl

proc replot val {
        puts stdout "p .c .y rs bs"
        flush stdout
}
set rs -1
set bs -1
global turn
set turn 0

global done
set done 0

##Label Canvas
#canvas .l -width 550 -height 20 -bg white
#pack .l -side top -pady 5

#.l create text 95 10 -text "Board"
#.l create text 450 10 -text "Shots"

##Top Board Canvas
canvas .c -width 300 -height 350 -bg white
pack .c -padx 20 -pady 20

.c create text 40 310 -text "Board"
.c create text 60 325 -text "Your Handle:" -tags handle

#.c create line 0 1 300 1 -width 1
.c create line 0 60 300 60 -width 2
.c create line 0 120 300 120 -width 2
.c create line 0 180 300 180 -width 2
.c create line 0 240 300 240 -width 2
.c create line 0 300 300 300 -width 2
#.c create line 1 0 1 300 -width 1
.c create line 60 0 60 300 -width 2
.c create line 120 0 120 300 -width 2
.c create line 180 0 180 300 -width 2
.c create line 240 0 240 300 -width 2
.c create line 300 0 300 300 -width 2
#create instantiations of the clickable spaces
.c create rectangle 0 0 60 60 -fill white -tags mBZero
.c create rectangle 60 0 120 60 -fill white -tags mBOne
.c create rectangle 120 0 180 60 -fill white -tags mBTwo
.c create rectangle 180 0 240 60 -fill white -tags mBThree
.c create rectangle 240 0 300 60 -fill white -tags mBFour
.c create rectangle 0 60 60 120 -fill white -tags mBFive
.c create rectangle 60 60 120 120 -fill white -tags mBSix
.c create rectangle 120 60 180 120 -fill white -tags mBSeven
.c create rectangle 180 60 240 120 -fill white -tags mBEight
.c create rectangle 240 60 300 120 -fill white -tags mBNine
.c create rectangle 0 120 60 180 -fill white -tags mBTen
.c create rectangle 60 120 120 180 -fill white -tags mBEleven
.c create rectangle 120 120 180 180 -fill white -tags mBTwelve
.c create rectangle 180 120 240 180 -fill white -tags mBThirteen
.c create rectangle 240 120 300 180 -fill white -tags mBFourteen
.c create rectangle 0 180 60 240 -fill white -tags mBFifteen
.c create rectangle 60 180 120 240 -fill white -tags mBSixteen
.c create rectangle 120 180 180 240 -fill white -tags mBSeventeen
.c create rectangle 180 180 240 240 -fill white -tags mBEighteen
.c create rectangle 240 180 300 240 -fill white -tags mBNineteen
.c create rectangle 0 240 60 300 -fill white -tags mBTwenty
.c create rectangle 60 240 120 300 -fill white -tags mBTOne
.c create rectangle 120 240 180 300 -fill white -tags mBTTwo
.c create rectangle 180 240 240 300 -fill white -tags mBTThree
.c create rectangle 240 240 300 300 -fill white -tags mBTFour

#create buttons of the rectangles
.c bind mBZero <Button-1> {\

    if {$rs==-1} {   
	  .c create oval 0 0 60 60 -fill black
	  set rs 0
	  puts 0
    } else {if {$bs==-1} {
	  .c create oval 0 0 60 60 -fill black
	  set bs 0
	  puts 0
    }}
    #.c itemconfigure mBZero -fill blue; \
    #if {$scolor == "navyblue"} {set scolor red} else {set scolor navyblue}
    }
.c bind mBOne <Button-1> {\
    if {$rs==-1} {   
    .c create oval 60 0 120 60 -fill black
    set rs 1
    puts 1
    } else {if {$bs==-1} {
    .c create oval 60 0 120 60 -fill black
    set bs 1
    puts 1
    }}
    #.c itemconfigure mBOne -fill blue; \
    #if {$scolor == "navyblue"} {set scolor red} else {set scolor navyblue}
    }
.c bind mBTwo <Button-1> {\
    if {$rs==-1} {   
    .c create oval 120 0 180 60 -fill black
    set rs 2
    puts 2
    } else {if {$bs==-1} {
    .c create oval 120 0 180 60 -fill black
    set bs 2
    puts 2
    }}
    #.c itemconfigure mBTwo -fill blue; \
    #if {$scolor == "navyblue"} {set scolor red} else {set scolor navyblue}
    }
.c bind mBThree <Button-1> {\
    if {$rs==-1} {   
    .c create oval 180 0 240 60 -fill black
    set rs 3
    puts 3
    } else {if {$bs==-1} {
    .c create oval 180 0 240 60 -fill black
    set bs 3
    puts 3
    }}
    #.c itemconfigure mBThree -fill blue; \
    #if {$scolor == "navyblue"} {set scolor red} else {set scolor navyblue}
    }
.c bind mBFour <Button-1> {\
    if {$rs==-1} {   
    .c create oval 240 0 300 60 -fill black
    set rs 4
    puts 4
    } else {if {$bs==-1} {
    .c create oval 240 0 300 60 -fill black
    set bs 4
    puts 4
    }}
    #.c itemconfigure mBFour -fill blue; \
    #if {$scolor == "navyblue"} {set scolor red} else {set scolor navyblue}
    }
.c bind mBFive <Button-1> {\
    if {$rs==-1} {   
    .c create oval 0 60 60 120 -fill black
    set rs 5
    puts 5
    } else {if {$bs==-1} {
    .c create oval 0 60 60 120 -fill black
    set bs 5
    puts 5
    }}
    #.c itemconfigure mBFive -fill blue; \
    #if {$scolor == "navyblue"} {set scolor red} else {set scolor navyblue}
    }
.c bind mBSix <Button-1> {\
    if {$rs==-1} {   
    .c create oval 60 60 120 120 -fill black
    set rs 6
    puts 6
    } else {if {$bs==-1} {
    .c create oval 60 60 120 120 -fill black
    set bs 6
    puts 6
    }}
    #.c itemconfigure mBSix -fill blue; \
    #if {$scolor == "navyblue"} {set scolor red} else {set scolor navyblue}
    }
.c bind mBSeven <Button-1> {\
    if {$rs==-1} {   
    .c create oval 120 60 180 120 -fill black
    set rs 7
    puts 7
    } else {if {$bs==-1} {
    .c create oval 120 60 180 120 -fill black
    set bs 7
    puts 7
    }}
    #.c itemconfigure mBSeven -fill blue; \
    #if {$scolor == "navyblue"} {set scolor red} else {set scolor navyblue}
    }
.c bind mBEight <Button-1> {\
    if {$rs==-1} {   
    .c create oval 180 60 240 120 -fill black
    set rs 8
    puts 8
    } else {if {$bs==-1} {
    .c create oval 180 60 240 120 -fill black
    set bs 8
    puts 8
    }}
    #.c itemconfigure mBEight -fill blue; \
    #if {$scolor == "navyblue"} {set scolor red} else {set scolor navyblue}
    }
.c bind mBNine <Button-1> {\
    if {$rs==-1} {   
    .c create oval 240 60 300 120 -fill black
    set rs 9
    puts 9
    } else {if {$bs==-1} {
    .c create oval 240 60 300 120 -fill black
    set bs 9
    puts 9
    }}
    #.c itemconfigure mBNine -fill blue; \
    #if {$scolor == "navyblue"} {set scolor red} else {set scolor navyblue}
    }

.c bind mBTen <Button-1> {\
    if {$rs==-1} {   
    .c create oval 0 120 60 180 -fill black
    set rs 10
    puts 10
    } else {if {$bs==-1} {
    .c create oval 0 120 60 180 -fill black
    set bs 10
    puts 10
    }}
    #.c itemconfigure mBTen -fill blue; \
    #if {$scolor == "navyblue"} {set scolor red} else {set scolor navyblue}
    }
.c bind mBEleven <Button-1> {\
    if {$rs==-1} {   
    .c create oval 60 120 120 180 -fill black
    set rs 11
    puts 11
    } else {if {$bs==-1} {
    .c create oval 60 120 120 180 -fill black
    set bs 11
    puts 11
    }}
    #.c itemconfigure mBEleven -fill blue; \
    #if {$scolor == "navyblue"} {set scolor red} else {set scolor navyblue}
    }
.c bind mBTwelve <Button-1> {\
    if {$rs==-1} {   
    .c create oval 120 120 180 180 -fill black
    set rs 12
    puts 12
    } else {if {$bs==-1} {
    .c create oval 120 120 180 180 -fill black
    set bs 12
    puts 12
    }}
    #.c itemconfigure mBTwelve -fill blue; \
    #if {$scolor == "navyblue"} {set scolor red} else {set scolor navyblue}
    }
.c bind mBThirteen <Button-1> {\
    if {$rs==-1} {   
    .c create oval 180 120 240 180 -fill black
    set rs 13
    puts 13
    } else {if {$bs==-1} {
    .c create oval 180 120 240 180 -fill black
    set bs 13
    puts 13
    }}
    #.c itemconfigure mBThirteen -fill blue; \
    #if {$scolor == "navyblue"} {set scolor red} else {set scolor navyblue}
    }
.c bind mBFourteen <Button-1> {\
    if {$rs==-1} {   
    .c create oval 240 120 300 180 -fill black
    set rs 14
    puts 14
    } else {if {$bs==-1} {
    .c create oval 240 120 300 180 -fill black
    set bs 14
    puts 14
    }}
    #.c itemconfigure mBFourteen -fill blue; \
    #if {$scolor == "navyblue"} {set scolor red} else {set scolor navyblue}
    }
.c bind mBFifteen <Button-1> {\
    if {$rs==-1} {   
    .c create oval 0 180 60 240 -fill black
    set rs 15
    puts 15
    } else {if {$bs==-1} {
    .c create oval 0 180 60 240 -fill black
    set bs 15
    puts 15
    }}
    #.c itemconfigure mBFifteen -fill blue; \
    #if {$scolor == "navyblue"} {set scolor red} else {set scolor navyblue}
    }
.c bind mBSixteen <Button-1> {\
    if {$rs==-1} {   
    .c create oval 60 180 120 240 -fill black
    set rs 16
    puts 16
    } else {if {$bs==-1} {
    .c create oval 60 180 120 240 -fill black
    set bs 16
    puts 16
    }}
    #.c itemconfigure mBSixteen -fill blue; \
    #if {$scolor == "navyblue"} {set scolor red} else {set scolor navyblue}
    }
.c bind mBSeventeen <Button-1> {\
    if {$rs==-1} {   
    .c create oval 120 180 180 240 -fill black
    set rs 17
    puts 17
    } else {if {$bs==-1} {
    .c create oval 120 180 180 240 -fill black
    set bs 17
    puts 17
    }}
    #.c itemconfigure mBSeventeen -fill blue; \
    #if {$scolor == "navyblue"} {set scolor red} else {set scolor navyblue}
    }
.c bind mBEighteen <Button-1> {\
    if {$rs==-1} {   
    .c create oval 180 180 240 240 -fill black
    set rs 18
    puts 18
    } else {if {$bs==-1} {
    .c create oval 180 180 240 240 -fill black
    set bs 18
    puts 18
    }}
    #.c itemconfigure mBEighteen -fill blue; \
    #if {$scolor == "navyblue"} {set scolor red} else {set scolor navyblue}
    }
.c bind mBNineteen <Button-1> {\
    if {$rs==-1} {   
    .c create oval 240 180 300 240 -fill black
    set rs 19
    puts 19
    } else {if {$bs==-1} {
    .c create oval 240 180 300 240 -fill black
    set bs 19
    puts 19
    }}
    #.c itemconfigure mBNineteen -fill blue; \
    #if {$scolor == "navyblue"} {set scolor red} else {set scolor navyblue}
    }
.c bind mBTwenty <Button-1> {\
    if {$rs==-1} {   
    .c create oval 0 240 60 300 -fill black
    set rs 20
    puts 20
    } else {if {$bs==-1} {
    .c create oval 0 240 60 300 -fill black
    set bs 20
    puts 20
    }}
    #.c itemconfigure mBTwenty -fill blue; \
    #if {$scolor == "navyblue"} {set scolor red} else {set scolor navyblue}
    }
.c bind mBTOne <Button-1> {\
    if {$rs==-1} {   
    .c create oval 60 240 120 300 -fill black
    set rs 21
    puts 21
    } else {if {$bs==-1} {
    .c create oval 60 240 120 300 -fill black
    set bs 21
    puts 21
    }}
    #.c itemconfigure mBTOne -fill blue; \
    #if {$scolor == "navyblue"} {set scolor red} else {set scolor navyblue}
    }
.c bind mBTTwo <Button-1> {\
    if {$rs==-1} {   
    .c create oval 120 240 180 300 -fill black
    set rs 22
    puts 22
    } else {if {$bs==-1} {
    .c create oval 120 240 180 300 -fill black
    set bs 22
    puts 22
    }}
    #.c itemconfigure mBTTwo -fill blue; \
    #if {$scolor == "navyblue"} {set scolor red} else {set scolor navyblue}
    }
.c bind mBTThree <Button-1> {\
    if {$rs==-1} {   
    .c create oval 180 240 240 300 -fill black
    set rs 23
    puts 23
    } else {if {$bs==-1} {
    .c create oval 180 240 240 300 -fill black
    set bs 23
    puts 23
    }}
    #.c itemconfigure mBTThree -fill blue; \
    #if {$scolor == "navyblue"} {set scolor red} else {set scolor navyblue}
    }
.c bind mBTFour <Button-1> {\
    if {$rs==-1} {   
    .c create oval 240 240 300 300 -fill black
    set rs 24
    puts 24
    } else {if {$bs==-1} {
    .c create oval 240 240 300 300 -fill black
    set bs 24
    puts 24
    }}
    #.c itemconfigure mBTFour -fill blue; \
    #if {$scolor == "navyblue"} {set scolor red} else {set scolor navyblue}
    }


#canvas .space -width 50 -height 300 -bg white
#pack .space -side left

##Lower Side Board Canvas
canvas .y -width 300 -height 350 -bg white
pack .y -padx 20 -pady 20

.y create text 40 310 -text "Shots"
.y create text 78 325 -text "Opponent's Handle:" -tags opphandle

.y create rectangle 0 0 60 60 -fill white -tags mBZero
.y create rectangle 60 0 120 60 -fill white -tags mBOne
.y create rectangle 120 0 180 60 -fill white -tags mBTwo
.y create rectangle 180 0 240 60 -fill white -tags mBThree
.y create rectangle 240 0 300 60 -fill white -tags mBFour
.y create rectangle 0 60 60 120 -fill white -tags mBFive
.y create rectangle 60 60 120 120 -fill white -tags mBSix
.y create rectangle 120 60 180 120 -fill white -tags mBSeven
.y create rectangle 180 60 240 120 -fill white -tags mBEight
.y create rectangle 240 60 300 120 -fill white -tags mBNine
.y create rectangle 0 120 60 180 -fill white -tags mBTen
.y create rectangle 60 120 120 180 -fill white -tags mBEleven
.y create rectangle 120 120 180 180 -fill white -tags mBTwelve
.y create rectangle 180 120 240 180 -fill white -tags mBThirteen
.y create rectangle 240 120 300 180 -fill white -tags mBFourteen
.y create rectangle 0 180 60 240 -fill white -tags mBFifteen
.y create rectangle 60 180 120 240 -fill white -tags mBSixteen
.y create rectangle 120 180 180 240 -fill white -tags mBSeventeen
.y create rectangle 180 180 240 240 -fill white -tags mBEighteen
.y create rectangle 240 180 300 240 -fill white -tags mBNineteen
.y create rectangle 0 240 60 300 -fill white -tags mBTwenty
.y create rectangle 60 240 120 300 -fill white -tags mBTOne
.y create rectangle 120 240 180 300 -fill white -tags mBTTwo
.y create rectangle 180 240 240 300 -fill white -tags mBTThree
.y create rectangle 240 240 300 300 -fill white -tags mBTFour


#All the flags
set y0 0; set y1 0; set y2 0; set y3 0; set y4 0; set y5 0; set y6 0; set y7 0; set y8 0; set y9 0; set y10 0;
set y11 0; set y11 0; set y12 0; set y13 0; set y14 0; set y15 0; set y16 0; set y17 0; set y18 0; set y19 0;
set y20 0; set y21 0; set y22 0; set y23 0; set y24 0;

#create buttons of the rectangles
.y bind mBZero <Button-1> {\
		if {$turn == 1} {\
    if {$y0 == 0} {puts 0; set y0 1; set turn 0} else {bell}
		}}
.y bind mBOne <Button-1> {\
		if {$turn == 1} {\
		if {$y1 == 0} {puts 1; set y1 1; set turn 0} else {bell}
		}}
.y bind mBTwo <Button-1> {\
		if {$turn == 1} {\
		if {$y2 == 0} {puts 2; set y2 1; set turn 0} else {bell}
		}}
.y bind mBThree <Button-1> {\
		if {$turn == 1} {\
		if {$y3 == 0} {puts 3; set y3 1; set turn 0} else {bell}
		}}
.y bind mBFour <Button-1> {\
		if {$turn == 1} {\
		if {$y4 == 0} {puts 4; set y4 1; set turn 0} else {bell}
    }}
.y bind mBFive <Button-1> {\
		if {$turn == 1} {\
		if {$y5 == 0} {puts 5; set y5 1; set turn 0} else {bell}
		}}
.y bind mBSix <Button-1> {\
		if {$turn == 1} {\
		if {$y6 == 0} {puts 6; set y6 1; set turn 0} else {bell}
		}}
.y bind mBSeven <Button-1> {\
		if {$turn == 1} {\
		if {$y7 == 0} {puts 7; set y7 1; set turn 0} else {bell}
		}}
.y bind mBEight <Button-1> {\
		if {$turn == 1} {\
		if {$y8 == 0} {puts 8; set y8 1; set turn 0} else {bell}
		}}
.y bind mBNine <Button-1> {\
		if {$turn == 1} {\
		if {$y9 == 0} {puts 9; set y9 1; set turn 0} else {bell}
		}}

.y bind mBTen <Button-1> {\
		if {$turn == 1} {\
		if {$y10 == 0} {puts 10; set y10 1; set turn 0} else {bell}
		}}
.y bind mBEleven <Button-1> {\
		if {$turn == 1} {\
		if {$y11 == 0} {puts 11; set y11 1; set turn 0} else {bell}
		}}
.y bind mBTwelve <Button-1> {\
		if {$turn == 1} {\
		if {$y12 == 0} {puts 12; set y12 1; set turn 0} else {bell}
		}}
.y bind mBThirteen <Button-1> {\
		if {$turn == 1} {\
		if {$y13 == 0} {puts 13; set y13 1; set turn 0} else {bell}
		}}
.y bind mBFourteen <Button-1> {\
		if {$turn == 1} {\
		if {$y14 == 0} {puts 14; set y14 1; set turn 0} else {bell}
		}}
.y bind mBFifteen <Button-1> {\
		if {$turn == 1} {\
		if {$y15 == 0} {puts 15; set y15 1; set turn 0} else {bell}
		}}
.y bind mBSixteen <Button-1> {\
		if {$turn == 1} {\
		if {$y16 == 0} {puts 16; set y16 1; set turn 0} else {bell}
		}}
.y bind mBSeventeen <Button-1> {\
		if {$turn == 1} {\
		if {$y17 == 0} {puts 17; set y17 1; set turn 0} else {bell}
		}}
.y bind mBEighteen <Button-1> {\
		if {$turn == 1} {\
		if {$y18 == 0} {puts 18; set y18 1; set turn 0} else {bell}
		}}
.y bind mBNineteen <Button-1> {\
		if {$turn == 1} {\
		if {$y19 == 0} {puts 19; set y19 1; set turn 0} else {bell}
		}}
.y bind mBTwenty <Button-1> {\
		if {$turn == 1} {\
		if {$y20 == 0} {puts 20; set y20 1; set turn 0} else {bell}
		}}
.y bind mBTOne <Button-1> {\
		if {$turn == 1} {\
		if {$y21 == 0} {puts 21; set y21 1; set turn 0} else {bell}
		}}
.y bind mBTTwo <Button-1> {\
		if {$turn == 1} {\
		if {$y22 == 0} {puts 22; set y22 1; set turn 0} else {bell}
		}}
.y bind mBTThree <Button-1> {\
		if {$turn == 1} {\
		if {$y23 == 0} {puts 23; set y23 1; set turn 0} else {bell}
		}}
.y bind mBTFour <Button-1> {\
		if {$turn == 1} {\
		if {$y24 == 0} {puts 24; set y24 1; set turn 0} else {bell}
		}}


##Status Canvas
canvas .s -width 300 -height 50 -bg white
pack .s -padx 20 -pady 20

.s create text 100 20 -text "Status: " -tags status
.s create text 200 20 -text " " -tags waiting
.s create text 150 40 -text " " -tags opp

# Frame for holding buttons
frame .bf 
pack  .bf -side bottom -anchor s -expand 1 -fill x

# Exit button
button .bf.e -text "Exit" -command {if {$done == 1} {exit}}

# Resign button
button .bf.r -text "Resign" -command {exit}


# Sound button
#button .bf.s -text "Silence" .bf.s

# Pack buttons into frame
pack .bf.e .bf.r  -side left \
	-expand 1 -fill x

##silence canvas
canvas .z -width 300 -height 50 -bg white
pack .z -padx 10 -pady 10

#.y create text 40 310 -text "Shots"

#Beep sounds...0 = no bell, 1 = bell
set silence 0 
.z create text 50 20 -text "\t\t\t\tSilence\t\t\t\t" -tags silence -font {-size 15}
.z bind  silence <Button-1> {\
if {$silence == 0} {set silence 1; .z itemconfigure silence -text "\t\t\t\tSound\t\t\t\t";}\
else {if {$silence == 1} {set silence 0; .z itemconfigure silence -text "\t\t\t\tSilence\t\t\t\t"}; bell}
}

#Call replot
#replot 0

