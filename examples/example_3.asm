mflr %r12
stw %r12, -0x8(%r1)
stwu %r1, -0x10(%r1)
li %r0, 5
sc
addi %r3, %r3, 0x3C
li %r5, 0x59
mr %r4, %r3
li %r3, 0xFF
li %r0, 6
sc
addi %r1, %r1, 0x10
lwz %r12, -0x8(%r1)
mtlr %r12
blr

# thread
addi %r3, %r3, 0x10
li %r0, 3
sc
blr