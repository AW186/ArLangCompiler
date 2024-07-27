; ModuleID = 'test/test1.al'
source_filename = "test/test1.al"

define double @main(double %argc) {
entry:
  br i1 true, label %then, label %else

then:                                             ; preds = %entry
  br label %ifcont

else:                                             ; preds = %entry
  br label %ifcont

ifcont:                                           ; preds = %else, %then
  ret float 1.000000e+00
}
