; ModuleID = 'test/test.al'
source_filename = "test/test.al"

define double @main(double %argc) {
entry:
  %0 = fadd double %argc, float 2.000000e+00
  %ifcond = fcmp one double %argc, 0.000000e+00
  br i1 %ifcond, label %then, label %else

then:                                             ; preds = %entry
  %1 = fadd double %0, float 1.000000e+02
  br label %ifcont

else:                                             ; preds = %entry
  br label %ifcont

ifcont:                                           ; preds = %else, %then
  ret double %1
}

define double @pow(double %base, double %exp) {
entry:
  %ifcond = fcmp one double %exp, 0.000000e+00
  br i1 %ifcond, label %then, label %else

then:                                             ; preds = %entry
  %0 = fsub double %exp, float 1.000000e+00
  %calltemp = call double @pow(double %base, double %0)
  ret double %calltemp
  br label %ifcont

else:                                             ; preds = %entry
  ret float 1.000000e+00
  br label %ifcont

ifcont:                                           ; preds = %else, %then
}

define double @pow2(double %base, double %exp) {
entry:
  br label %loop

loop:                                             ; preds = %loop1, %entry
  %loopcond = fcmp one double %exp, 0.000000e+00
  br i1 %loopcond, label %loop1, label %else

loop1:                                            ; preds = %loop
  %0 = fmul float 1.000000e+00, double %base
  %1 = fsub double %exp, float 1.000000e+00
  br label %loop

else:                                             ; preds = %loop
  ret float %0
}
