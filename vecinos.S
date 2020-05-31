.globl vecinos

#define PADDING_X 1
#define PADDING_Y 1

# Stack size
#define SS 8

# Offset to each argument in the ABA
#define O_ARG0(sp) (SS + 0)(sp)
#define O_ARG1(sp) (SS + 4)(sp)
#define O_ARG2(sp) (SS + 8)(sp)
#define O_ARG3(sp) (SS + 12)(sp)
#define O_ARG4(sp) (SS + 16)(sp)

# Offset to fp and gp
#define O_FP(sp) (SS-4)(sp)
#define O_GP(sp) (SS-8)(sp)

# #############################################################################
#
# int vecinos(unsigned char* board, unsigned int i, unsigned int j, unsigned int rows, unsigned int columns)
#
# Assembly implementation of the vecinos function.
#
# Stack usage:
#  [SS - O_GP]
#  [SS - O_FP]
#
# Register usage:
#  -- Arguments --
# $a0: char* board
# $a1: unsigned int i
# $a2: unsigned int j
# $a3: unsigned int rows
# $t7: unsigned int columns
# 
# $t0: i iterator for outter
# $t1: i iterator for inner
# #############################################################################
vecinos:
    addiu   $sp, $sp, -SS             # Create the stack frame

    # Set up ABA and load fifth argument into registers
    sw      $a0, O_ARG0($sp)         # Store $a0 in the ABA
    sw      $a1, O_ARG1($sp)         # Store $a1 in the ABA
    sw      $a2, O_ARG2($sp)         # Store $a2 in the ABA
    sw      $a3, O_ARG3($sp)         # Store $a3 in the ABA
    lw      $t7, O_ARG4($sp)         # Load fifth argument (iterations)

    # Store fp and gp
    sw	$fp, O_FP($sp)		# Store fp in the ABA
    sw	$gp, O_GP($sp)		# Store gp in the ABA

    # Set neighbout count
    addi  $v0, $zero, 0

    # Start for loop
    li    $t0, -1
  outer_loop:
    bge  $t0, 2, end
    li    $t1, -1

    # Set row neightbour position
    add  $t2, $a1, $t0
    add   $t2, $t2, $a3
    remu  $t2, $t2, $a3

    #fijo la proxima posicion
    addi $t0, $t0, 1
  inner_loop:
    bge  $t1, 2, outer_loop

    # Set column neightbour position
    add   $t3, $a2, $t1
    add   $t3, $t3, $t7
    remu  $t3, $t3, $t7

    # Find and add neightbour
    mul   $t4, $t3, $a3 # multiply $t4 = (row) * (column-neighbour)
    add   $t4, $t4, $t2 # add $t4 = $t4 + (row-neighbour)
    add   $t4, $t4, $a0 # add address and save to t4.
    lb    $t5, 0($t4)
    add   $v0, $v0, $t5

    # Check not to sum original position
    bne   $t0, 1, add2
    addi  $t1, $t1, 1
  add2:
    addi  $t1, $t1, 1
    b inner_loop

  end:
    # Stack unwind
    lw    $fp, O_FP($sp)
    lw    $gp, O_GP($sp)
    addiu $sp, $sp, SS

    # Return
    jr  $ra
