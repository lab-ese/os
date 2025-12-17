#!/usr/bin/awk -f

# AWK Program to generate student result report
# Input format: RollNo Name Subject1 Subject2 Subject3

BEGIN {
    print "======================================================================"
    print "                    STUDENT RESULT REPORT                             "
    print "======================================================================"
    printf "%-10s %-15s %-8s %-8s %-8s %-8s %-8s %-10s\n", "Roll No", "Name", "Sub1", "Sub2", "Sub3", "Total", "Average", "Result"
    print "----------------------------------------------------------------------"
}

{
    rollno = $1
    name = $2
    sub1 = $3
    sub2 = $4
    sub3 = $5
    
    total = sub1 + sub2 + sub3
    average = total / 3
    
    # Check if student passed (assuming minimum 40 marks in each subject)
    if (sub1 >= 40 && sub2 >= 40 && sub3 >= 40 && average >= 50) {
        result = "PASS"
    } else {
        result = "FAIL"
    }
    
    printf "%-10s %-15s %-8d %-8d %-8d %-8d %-8.2f %-10s\n", rollno, name, sub1, sub2, sub3, total, average, result
}

END {
    print "======================================================================"
    print "                         END OF REPORT                                "
    print "======================================================================"
}
