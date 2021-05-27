mflr %r12
stw %r12, -0x8(%r1)
stwu %r1, -0x10(%r1)
li %r0, 5
sc
addi %r3, %r3, 0x38
mr %r4, %r3
li %r3, 0xFF
li %r0, 6
sc
addi %r1, %r1, 0x10
lwz %r12, -0x8(%r1)
mtlr %r12
blr

# thread
li %r3, 0x69
li %r0, 3
sc
blr