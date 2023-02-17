(module
  (type (;0;) (func (result i32)))
  (type (;1;) (func (param i32) (result i32)))
  (type (;2;) (func (param i32)))
  (type (;3;) (func (param i32 i32 i32) (result i32)))
  (type (;4;) (func (param i32 i32) (result i32)))
  (type (;5;) (func (param i32) (result i64)))
  (func $readSeq (type 1) (param i32) (result i32)
    (local i32)
    global.get $__stack_pointer
    i32.const 32
    i32.sub
    local.tee 1
    global.set $__stack_pointer
    local.get 1
    local.get 0
    i32.store offset=28
    local.get 1
    i32.const 0
    i32.store offset=24
    local.get 1
    i32.const 4
    i32.store offset=20
    local.get 1
    i32.load offset=20
    i32.const 2
    i32.shl
    call $malloc
    local.set 0
    local.get 1
    i32.load offset=28
    local.get 0
    i32.store
    local.get 1
    i32.const 32
    i32.store offset=16
    loop  ;; label = @1
      i32.const 0
      local.set 0
      block  ;; label = @2
        i32.const -1
        local.get 1
        i32.load offset=16
        i32.ne
        i32.const 1
        i32.and
        i32.eqz
        br_if 0 (;@2;)
        i32.const 10
        local.get 1
        i32.load offset=16
        i32.ne
        local.set 0
      end
      block  ;; label = @2
        local.get 0
        i32.const 1
        i32.and
        i32.eqz
        br_if 0 (;@2;)
        i32.const 1024
        call $__WASP_symb_int
        local.set 0
        local.get 1
        i32.load offset=28
        i32.load
        local.get 1
        i32.load offset=24
        i32.const 2
        i32.shl
        i32.add
        local.get 0
        i32.store
        local.get 1
        local.get 1
        i32.load offset=28
        i32.load
        local.get 1
        i32.load offset=24
        i32.const 2
        i32.shl
        i32.add
        i32.store
        i32.const 1026
        local.get 1
        call $scanf
        drop
        local.get 1
        call $getchar
        i32.const 24
        i32.shl
        i32.const 24
        i32.shr_s
        i32.store offset=16
        local.get 1
        local.get 1
        i32.load offset=24
        i32.const 1
        i32.add
        i32.store offset=24
        block  ;; label = @3
          local.get 1
          i32.load offset=20
          local.get 1
          i32.load offset=24
          i32.const 1
          i32.add
          i32.eq
          i32.const 1
          i32.and
          i32.eqz
          br_if 0 (;@3;)
          local.get 1
          local.get 1
          i32.load offset=20
          i32.const 1
          i32.shl
          i32.store offset=20
          local.get 1
          i32.load offset=28
          i32.load
          local.get 1
          i32.load offset=20
          i32.const 2
          i32.shl
          call $realloc
          local.set 0
          local.get 1
          i32.load offset=28
          local.get 0
          i32.store
        end
        br 1 (;@1;)
      end
    end
    local.get 1
    i32.load offset=28
    i32.load
    local.get 1
    i32.load offset=24
    i32.const 2
    i32.shl
    i32.add
    i32.const 2147483647
    i32.store
    local.get 1
    local.get 1
    i32.load offset=24
    i32.const 1
    i32.add
    i32.store offset=24
    local.get 1
    i32.load offset=24
    local.set 0
    local.get 1
    i32.const 32
    i32.add
    global.set $__stack_pointer
    local.get 0)
  (func $newS (type 0) (result i32)
    (local i32 i32)
    global.get $__stack_pointer
    i32.const 16
    i32.sub
    local.tee 0
    global.set $__stack_pointer
    local.get 0
    i32.const 0
    i32.store offset=12
    local.get 0
    i32.const 12
    call $malloc
    i32.store offset=12
    local.get 0
    i32.load offset=12
    i32.const 4
    i32.store offset=4
    local.get 0
    i32.load offset=12
    i32.const 0
    i32.store
    local.get 0
    i32.load offset=12
    i32.load offset=4
    i32.const 3
    i32.shl
    call $malloc
    local.set 1
    local.get 0
    i32.load offset=12
    local.get 1
    i32.store offset=8
    local.get 0
    i32.load offset=12
    i32.load offset=8
    i32.const 2147483647
    i32.store
    local.get 0
    i32.load offset=12
    i32.load offset=8
    i32.const 0
    i32.store offset=4
    local.get 0
    i32.load offset=12
    local.set 1
    local.get 0
    i32.const 16
    i32.add
    global.set $__stack_pointer
    local.get 1)
  (func $freeS (type 2) (param i32)
    (local i32)
    global.get $__stack_pointer
    i32.const 16
    i32.sub
    local.tee 1
    global.set $__stack_pointer
    local.get 1
    local.get 0
    i32.store offset=12
    local.get 1
    i32.load offset=12
    i32.load offset=8
    call $free
    local.get 1
    i32.load offset=12
    i32.const 0
    i32.store offset=8
    local.get 1
    i32.load offset=12
    call $free
    local.get 1
    i32.const 16
    i32.add
    global.set $__stack_pointer)
  (func $top (type 1) (param i32) (result i32)
    (local i32)
    global.get $__stack_pointer
    i32.const 16
    i32.sub
    local.tee 1
    local.get 0
    i32.store offset=12
    local.get 1
    i32.load offset=12
    i32.load offset=8
    local.get 1
    i32.load offset=12
    i32.load
    i32.const 3
    i32.shl
    i32.add)
  (func $pump (type 2) (param i32)
    (local i32)
    global.get $__stack_pointer
    i32.const 16
    i32.sub
    local.tee 1
    global.set $__stack_pointer
    local.get 1
    local.get 0
    i32.store offset=12
    local.get 1
    i32.load offset=12
    local.tee 0
    local.get 0
    i32.load
    i32.const 1
    i32.add
    i32.store
    block  ;; label = @1
      local.get 1
      i32.load offset=12
      i32.load offset=4
      local.get 1
      i32.load offset=12
      i32.load
      i32.eq
      i32.const 1
      i32.and
      i32.eqz
      br_if 0 (;@1;)
      local.get 1
      i32.load offset=12
      local.tee 0
      local.get 0
      i32.load offset=4
      i32.const 1
      i32.shl
      i32.store offset=4
      local.get 1
      i32.load offset=12
      i32.load offset=8
      local.get 1
      i32.load offset=12
      i32.load offset=4
      i32.const 3
      i32.shl
      call $realloc
      local.set 0
      local.get 1
      i32.load offset=12
      local.get 0
      i32.store offset=8
    end
    local.get 1
    i32.const 16
    i32.add
    global.set $__stack_pointer)
  (func $topBSearch (type 3) (param i32 i32 i32) (result i32)
    (local i32)
    global.get $__stack_pointer
    i32.const 32
    i32.sub
    local.tee 3
    global.set $__stack_pointer
    local.get 3
    local.get 0
    i32.store offset=28
    local.get 3
    local.get 1
    i32.store offset=24
    local.get 3
    local.get 2
    i32.store offset=20
    local.get 3
    i32.const 0
    i32.store offset=12
    local.get 3
    local.get 3
    i32.load offset=24
    i32.store offset=8
    block  ;; label = @1
      loop  ;; label = @2
        local.get 3
        i32.load offset=12
        i32.const 1
        i32.add
        local.get 3
        i32.load offset=8
        i32.lt_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        local.get 3
        local.get 3
        i32.load offset=8
        local.get 3
        i32.load offset=12
        i32.add
        i32.store offset=16
        local.get 3
        local.get 3
        i32.load offset=16
        i32.const 2
        i32.div_s
        i32.store offset=16
        block  ;; label = @3
          block  ;; label = @4
            local.get 3
            i32.load offset=28
            local.get 3
            i32.load offset=16
            i32.const 2
            i32.shl
            i32.add
            i32.load
            call $top
            i32.load
            local.get 3
            i32.load offset=20
            i32.gt_s
            i32.const 1
            i32.and
            i32.eqz
            br_if 0 (;@4;)
            local.get 3
            local.get 3
            i32.load offset=16
            i32.store offset=8
            br 1 (;@3;)
          end
          local.get 3
          local.get 3
          i32.load offset=16
          i32.store offset=12
        end
        br 0 (;@2;)
      end
    end
    block  ;; label = @1
      local.get 3
      i32.load offset=28
      local.get 3
      i32.load offset=12
      i32.const 2
      i32.shl
      i32.add
      i32.load
      call $top
      i32.load
      local.get 3
      i32.load offset=20
      i32.lt_s
      i32.const 1
      i32.and
      i32.eqz
      br_if 0 (;@1;)
      local.get 3
      local.get 3
      i32.load offset=12
      i32.const 1
      i32.add
      i32.store offset=12
    end
    local.get 3
    i32.load offset=12
    local.set 0
    local.get 3
    i32.const 32
    i32.add
    global.set $__stack_pointer
    local.get 0)
  (func $stackBSearch (type 4) (param i32 i32) (result i32)
    (local i32)
    global.get $__stack_pointer
    i32.const 32
    i32.sub
    local.tee 2
    local.get 0
    i32.store offset=28
    local.get 2
    local.get 1
    i32.store offset=24
    local.get 2
    i32.const 0
    i32.store offset=16
    local.get 2
    local.get 2
    i32.load offset=28
    i32.load
    i32.const 1
    i32.add
    i32.store offset=12
    block  ;; label = @1
      loop  ;; label = @2
        local.get 2
        i32.load offset=16
        i32.const 1
        i32.add
        local.get 2
        i32.load offset=12
        i32.lt_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        local.get 2
        local.get 2
        i32.load offset=12
        local.get 2
        i32.load offset=16
        i32.add
        i32.store offset=20
        local.get 2
        local.get 2
        i32.load offset=20
        i32.const 2
        i32.div_s
        i32.store offset=20
        block  ;; label = @3
          block  ;; label = @4
            local.get 2
            i32.load offset=28
            i32.load offset=8
            local.get 2
            i32.load offset=20
            i32.const 3
            i32.shl
            i32.add
            i32.load
            local.get 2
            i32.load offset=24
            i32.lt_s
            i32.const 1
            i32.and
            i32.eqz
            br_if 0 (;@4;)
            local.get 2
            local.get 2
            i32.load offset=20
            i32.store offset=12
            br 1 (;@3;)
          end
          local.get 2
          local.get 2
          i32.load offset=20
          i32.store offset=16
        end
        br 0 (;@2;)
      end
    end
    local.get 2
    i32.load offset=28
    i32.load offset=8
    local.get 2
    i32.load offset=16
    i32.const 3
    i32.shl
    i32.add
    i32.load offset=4)
  (func $__original_main (type 0) (result i32)
    (local i32 i32 i32)
    global.get $__stack_pointer
    i32.const 96
    i32.sub
    local.tee 0
    global.set $__stack_pointer
    local.get 0
    i32.const 1029
    call $__WASP_symb_int
    i32.store offset=80
    call $getchar
    drop
    local.get 0
    local.get 0
    i32.const 72
    i32.add
    call $readSeq
    i32.store offset=76
    block  ;; label = @1
      block  ;; label = @2
        block  ;; label = @3
          local.get 0
          i32.load offset=80
          local.tee 1
          i32.const 1
          i32.eq
          br_if 0 (;@3;)
          local.get 1
          i32.const 2
          i32.eq
          br_if 1 (;@2;)
          br 2 (;@1;)
        end
        local.get 0
        local.get 0
        i32.load offset=76
        i32.const -1
        i32.add
        i32.store offset=76
        local.get 0
        local.get 0
        i32.load offset=76
        i32.const 1
        i32.add
        i32.const 4
        call $calloc
        i32.store offset=92
        call $newS
        local.set 1
        local.get 0
        i32.load offset=92
        local.get 1
        i32.store
        local.get 0
        i32.load offset=92
        i32.load
        call $pump
        local.get 0
        i32.load offset=92
        i32.load
        call $top
        i32.const -2147483648
        i32.store
        local.get 0
        i32.load offset=92
        i32.load
        call $top
        i32.const 1
        i32.store offset=4
        local.get 0
        i32.const 1
        i32.store offset=64
        local.get 0
        i32.const 0
        i32.store offset=68
        block  ;; label = @3
          loop  ;; label = @4
            local.get 0
            i32.load offset=68
            local.get 0
            i32.load offset=76
            i32.lt_s
            i32.const 1
            i32.and
            i32.eqz
            br_if 1 (;@3;)
            local.get 0
            local.get 0
            i32.load offset=92
            local.get 0
            i32.load offset=64
            local.get 0
            i32.load offset=72
            local.get 0
            i32.load offset=68
            i32.const 2
            i32.shl
            i32.add
            i32.load
            call $topBSearch
            i32.store offset=56
            block  ;; label = @5
              local.get 0
              i32.load offset=64
              local.get 0
              i32.load offset=56
              i32.eq
              i32.const 1
              i32.and
              i32.eqz
              br_if 0 (;@5;)
              call $newS
              local.set 1
              local.get 0
              i32.load offset=92
              local.get 0
              i32.load offset=64
              i32.const 2
              i32.shl
              i32.add
              local.get 1
              i32.store
              local.get 0
              local.get 0
              i32.load offset=64
              i32.const 1
              i32.add
              i32.store offset=64
            end
            local.get 0
            local.get 0
            i32.load offset=92
            local.get 0
            i32.load offset=56
            i32.const 2
            i32.shl
            i32.add
            i32.load
            call $top
            i32.load offset=4
            i32.store offset=40
            local.get 0
            i32.load offset=92
            local.get 0
            i32.load offset=56
            i32.const 2
            i32.shl
            i32.add
            i32.load
            call $pump
            local.get 0
            i32.load offset=72
            local.get 0
            i32.load offset=68
            i32.const 2
            i32.shl
            i32.add
            i32.load
            local.set 1
            local.get 0
            i32.load offset=92
            local.get 0
            i32.load offset=56
            i32.const 2
            i32.shl
            i32.add
            i32.load
            call $top
            local.get 1
            i32.store
            local.get 0
            i32.load offset=40
            local.set 1
            local.get 0
            i32.load offset=92
            local.get 0
            i32.load offset=56
            i32.const 2
            i32.shl
            i32.add
            i32.load
            call $top
            local.get 1
            i32.store offset=4
            local.get 0
            i32.load offset=92
            local.get 0
            i32.load offset=56
            i32.const 1
            i32.sub
            i32.const 2
            i32.shl
            i32.add
            i32.load
            call $top
            i32.load offset=4
            local.set 1
            local.get 0
            i32.load offset=92
            local.get 0
            i32.load offset=56
            i32.const 2
            i32.shl
            i32.add
            i32.load
            call $top
            local.tee 2
            local.get 1
            local.get 2
            i32.load offset=4
            i32.add
            i32.store offset=4
            local.get 0
            i32.load offset=92
            local.get 0
            i32.load offset=56
            i32.const 1
            i32.sub
            i32.const 2
            i32.shl
            i32.add
            i32.load
            local.get 0
            i32.load offset=72
            local.get 0
            i32.load offset=68
            i32.const 2
            i32.shl
            i32.add
            i32.load
            call $stackBSearch
            local.set 1
            local.get 0
            i32.load offset=92
            local.get 0
            i32.load offset=56
            i32.const 2
            i32.shl
            i32.add
            i32.load
            call $top
            local.tee 2
            local.get 2
            i32.load offset=4
            local.get 1
            i32.sub
            i32.store offset=4
            local.get 0
            local.get 0
            i32.load offset=68
            i32.const 1
            i32.add
            i32.store offset=68
            br 0 (;@4;)
          end
        end
        local.get 0
        local.get 0
        i32.load offset=64
        i32.const -1
        i32.add
        i32.store offset=64
        local.get 0
        local.get 0
        i32.load offset=64
        i32.store
        i32.const 1047
        local.get 0
        call $printf
        drop
        local.get 0
        local.get 0
        i32.load offset=92
        local.get 0
        i32.load offset=64
        i32.const 2
        i32.shl
        i32.add
        i32.load
        call $top
        i32.load offset=4
        i32.store offset=16
        i32.const 1051
        local.get 0
        i32.const 16
        i32.add
        call $printf
        drop
        local.get 0
        i32.const 0
        i32.store offset=68
        block  ;; label = @3
          loop  ;; label = @4
            local.get 0
            i32.load offset=68
            local.get 0
            i32.load offset=64
            i32.le_s
            i32.const 1
            i32.and
            i32.eqz
            br_if 1 (;@3;)
            local.get 0
            i32.load offset=92
            local.get 0
            i32.load offset=68
            i32.const 2
            i32.shl
            i32.add
            i32.load
            call $freeS
            local.get 0
            local.get 0
            i32.load offset=68
            i32.const 1
            i32.add
            i32.store offset=68
            br 0 (;@4;)
          end
        end
        local.get 0
        i32.load offset=92
        call $free
        br 1 (;@1;)
      end
      local.get 0
      local.get 0
      i32.const 60
      i32.add
      call $readSeq
      i32.store offset=56
      local.get 0
      i32.const 4
      i32.store offset=52
      local.get 0
      local.get 0
      i32.load offset=52
      i32.const 3
      i32.shl
      call $malloc
      i32.store offset=48
      local.get 0
      i32.const 0
      i32.store offset=44
      local.get 0
      i32.const 0
      i32.store offset=68
      block  ;; label = @2
        loop  ;; label = @3
          local.get 0
          i32.load offset=68
          local.get 0
          i32.load offset=76
          i32.lt_s
          i32.const 1
          i32.and
          i32.eqz
          br_if 1 (;@2;)
          local.get 0
          i32.const 0
          i32.store offset=64
          block  ;; label = @4
            loop  ;; label = @5
              local.get 0
              i32.load offset=64
              local.get 0
              i32.load offset=56
              i32.lt_s
              i32.const 1
              i32.and
              i32.eqz
              br_if 1 (;@4;)
              block  ;; label = @6
                local.get 0
                i32.load offset=72
                local.get 0
                i32.load offset=68
                i32.const 2
                i32.shl
                i32.add
                i32.load
                local.get 0
                i32.load offset=60
                local.get 0
                i32.load offset=64
                i32.const 2
                i32.shl
                i32.add
                i32.load
                i32.eq
                i32.const 1
                i32.and
                i32.eqz
                br_if 0 (;@6;)
                local.get 0
                i32.load offset=48
                local.get 0
                i32.load offset=44
                i32.const 3
                i32.shl
                i32.add
                local.get 0
                i32.load offset=68
                i32.store
                local.get 0
                i32.load offset=48
                local.get 0
                i32.load offset=44
                i32.const 3
                i32.shl
                i32.add
                local.get 0
                i32.load offset=64
                i32.store offset=4
                local.get 0
                local.get 0
                i32.load offset=44
                i32.const 1
                i32.add
                i32.store offset=44
                block  ;; label = @7
                  local.get 0
                  i32.load offset=52
                  local.get 0
                  i32.load offset=44
                  i32.eq
                  i32.const 1
                  i32.and
                  i32.eqz
                  br_if 0 (;@7;)
                  local.get 0
                  local.get 0
                  i32.load offset=52
                  i32.const 1
                  i32.shl
                  i32.store offset=52
                  local.get 0
                  local.get 0
                  i32.load offset=48
                  local.get 0
                  i32.load offset=52
                  i32.const 3
                  i32.shl
                  call $realloc
                  i32.store offset=48
                end
              end
              local.get 0
              local.get 0
              i32.load offset=64
              i32.const 1
              i32.add
              i32.store offset=64
              br 0 (;@5;)
            end
          end
          local.get 0
          local.get 0
          i32.load offset=68
          i32.const 1
          i32.add
          i32.store offset=68
          br 0 (;@3;)
        end
      end
      local.get 0
      i32.load offset=60
      call $free
      local.get 0
      local.get 0
      i32.load offset=44
      i32.const 2
      i32.shl
      call $malloc
      i32.store offset=88
      local.get 0
      local.get 0
      i32.load offset=44
      i32.const 2
      i32.shl
      call $malloc
      i32.store offset=84
      local.get 0
      i32.const 0
      i32.store offset=68
      block  ;; label = @2
        loop  ;; label = @3
          local.get 0
          i32.load offset=68
          local.get 0
          i32.load offset=44
          i32.lt_s
          i32.const 1
          i32.and
          i32.eqz
          br_if 1 (;@2;)
          local.get 0
          i32.load offset=88
          local.get 0
          i32.load offset=68
          i32.const 2
          i32.shl
          i32.add
          i32.const 1
          i32.store
          local.get 0
          i32.load offset=84
          local.get 0
          i32.load offset=68
          i32.const 2
          i32.shl
          i32.add
          i32.const 1
          i32.store
          local.get 0
          i32.const 0
          i32.store offset=64
          block  ;; label = @4
            loop  ;; label = @5
              local.get 0
              i32.load offset=64
              local.get 0
              i32.load offset=68
              i32.lt_s
              i32.const 1
              i32.and
              i32.eqz
              br_if 1 (;@4;)
              block  ;; label = @6
                local.get 0
                i32.load offset=48
                local.get 0
                i32.load offset=64
                i32.const 3
                i32.shl
                i32.add
                i32.load offset=4
                local.get 0
                i32.load offset=48
                local.get 0
                i32.load offset=68
                i32.const 3
                i32.shl
                i32.add
                i32.load offset=4
                i32.lt_s
                i32.const 1
                i32.and
                i32.eqz
                br_if 0 (;@6;)
                local.get 0
                i32.load offset=72
                local.get 0
                i32.load offset=48
                local.get 0
                i32.load offset=64
                i32.const 3
                i32.shl
                i32.add
                i32.load
                i32.const 2
                i32.shl
                i32.add
                i32.load
                local.get 0
                i32.load offset=72
                local.get 0
                i32.load offset=48
                local.get 0
                i32.load offset=68
                i32.const 3
                i32.shl
                i32.add
                i32.load
                i32.const 2
                i32.shl
                i32.add
                i32.load
                i32.lt_s
                i32.const 1
                i32.and
                i32.eqz
                br_if 0 (;@6;)
                local.get 0
                i32.load offset=88
                local.get 0
                i32.load offset=68
                i32.const 2
                i32.shl
                i32.add
                i32.load
                local.get 0
                i32.load offset=88
                local.get 0
                i32.load offset=64
                i32.const 2
                i32.shl
                i32.add
                i32.load
                i32.const 1
                i32.add
                i32.lt_s
                i32.const 1
                i32.and
                i32.eqz
                br_if 0 (;@6;)
                local.get 0
                i32.load offset=88
                local.get 0
                i32.load offset=68
                i32.const 2
                i32.shl
                i32.add
                local.get 0
                i32.load offset=88
                local.get 0
                i32.load offset=64
                i32.const 2
                i32.shl
                i32.add
                i32.load
                i32.const 1
                i32.add
                i32.store
                local.get 0
                i32.load offset=84
                local.get 0
                i32.load offset=68
                i32.const 2
                i32.shl
                i32.add
                i32.const 0
                i32.store
              end
              local.get 0
              local.get 0
              i32.load offset=64
              i32.const 1
              i32.add
              i32.store offset=64
              br 0 (;@5;)
            end
          end
          local.get 0
          i32.const 0
          i32.store offset=64
          block  ;; label = @4
            loop  ;; label = @5
              local.get 0
              i32.load offset=64
              local.get 0
              i32.load offset=68
              i32.lt_s
              i32.const 1
              i32.and
              i32.eqz
              br_if 1 (;@4;)
              block  ;; label = @6
                local.get 0
                i32.load offset=48
                local.get 0
                i32.load offset=64
                i32.const 3
                i32.shl
                i32.add
                i32.load offset=4
                local.get 0
                i32.load offset=48
                local.get 0
                i32.load offset=68
                i32.const 3
                i32.shl
                i32.add
                i32.load offset=4
                i32.lt_s
                i32.const 1
                i32.and
                i32.eqz
                br_if 0 (;@6;)
                local.get 0
                i32.load offset=72
                local.get 0
                i32.load offset=48
                local.get 0
                i32.load offset=64
                i32.const 3
                i32.shl
                i32.add
                i32.load
                i32.const 2
                i32.shl
                i32.add
                i32.load
                local.get 0
                i32.load offset=72
                local.get 0
                i32.load offset=48
                local.get 0
                i32.load offset=68
                i32.const 3
                i32.shl
                i32.add
                i32.load
                i32.const 2
                i32.shl
                i32.add
                i32.load
                i32.lt_s
                i32.const 1
                i32.and
                i32.eqz
                br_if 0 (;@6;)
                local.get 0
                i32.load offset=88
                local.get 0
                i32.load offset=68
                i32.const 2
                i32.shl
                i32.add
                i32.load
                local.get 0
                i32.load offset=88
                local.get 0
                i32.load offset=64
                i32.const 2
                i32.shl
                i32.add
                i32.load
                i32.const 1
                i32.add
                i32.eq
                i32.const 1
                i32.and
                i32.eqz
                br_if 0 (;@6;)
                local.get 0
                i32.load offset=84
                local.get 0
                i32.load offset=68
                i32.const 2
                i32.shl
                i32.add
                local.tee 1
                local.get 1
                i32.load
                local.get 0
                i32.load offset=84
                local.get 0
                i32.load offset=64
                i32.const 2
                i32.shl
                i32.add
                i32.load
                i32.add
                i32.store
              end
              local.get 0
              local.get 0
              i32.load offset=64
              i32.const 1
              i32.add
              i32.store offset=64
              br 0 (;@5;)
            end
          end
          local.get 0
          local.get 0
          i32.load offset=68
          i32.const 1
          i32.add
          i32.store offset=68
          br 0 (;@3;)
        end
      end
      local.get 0
      local.get 0
      i32.load offset=88
      local.get 0
      i32.load offset=44
      i32.const 1
      i32.sub
      i32.const 2
      i32.shl
      i32.add
      i32.load
      i32.const 1
      i32.sub
      i32.store offset=32
      i32.const 1051
      local.get 0
      i32.const 32
      i32.add
      call $printf
      drop
      local.get 0
      i32.load offset=88
      call $free
      local.get 0
      i32.load offset=84
      call $free
      local.get 0
      i32.load offset=48
      call $free
    end
    local.get 0
    i32.load offset=72
    call $free
    local.get 0
    i32.const 96
    i32.add
    global.set $__stack_pointer
    i32.const 0)
  (func $printf (type 4) (param i32 i32) (result i32)
    (local i32 i32 i32 i32)
    global.get $__stack_pointer
    local.set 2
    i32.const 16
    local.set 3
    local.get 2
    local.get 3
    i32.sub
    local.set 4
    local.get 4
    local.get 0
    i32.store offset=12
    i32.const 0
    local.set 5
    local.get 5
    return)
  (func $scanf (type 4) (param i32 i32) (result i32)
    (local i32 i32 i32 i32)
    global.get $__stack_pointer
    local.set 2
    i32.const 16
    local.set 3
    local.get 2
    local.get 3
    i32.sub
    local.set 4
    local.get 4
    local.get 0
    i32.store offset=12
    i32.const 0
    local.set 5
    local.get 5
    return)
  (func $summ_new_sym_var (type 1) (param i32) (result i32)
    (local i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i64 i32 i32 i32 i32)
    global.get $__stack_pointer
    local.set 1
    i32.const 16
    local.set 2
    local.get 1
    local.get 2
    i32.sub
    local.set 3
    local.get 3
    global.set $__stack_pointer
    local.get 3
    local.get 0
    i32.store offset=8
    local.get 3
    i32.load offset=8
    local.set 4
    i32.const 32
    local.set 5
    local.get 4
    local.set 6
    local.get 5
    local.set 7
    local.get 6
    local.get 7
    i32.le_u
    local.set 8
    i32.const 1
    local.set 9
    local.get 8
    local.get 9
    i32.and
    local.set 10
    block  ;; label = @1
      block  ;; label = @2
        local.get 10
        i32.eqz
        br_if 0 (;@2;)
        i32.const 1039
        local.set 11
        local.get 11
        call $__WASP_symb_int
        local.set 12
        local.get 3
        local.get 12
        i32.store offset=12
        br 1 (;@1;)
      end
      i32.const 1031
      local.set 13
      local.get 13
      call $__WASP_symb_long
      local.set 14
      local.get 14
      i32.wrap_i64
      local.set 15
      local.get 3
      local.get 15
      i32.store offset=12
    end
    local.get 3
    i32.load offset=12
    local.set 16
    i32.const 16
    local.set 17
    local.get 3
    local.get 17
    i32.add
    local.set 18
    local.get 18
    global.set $__stack_pointer
    local.get 16
    return)
  (func $getchar1 (type 0) (result i32)
    (local i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32)
    global.get $__stack_pointer
    local.set 0
    i32.const 16
    local.set 1
    local.get 0
    local.get 1
    i32.sub
    local.set 2
    local.get 2
    global.set $__stack_pointer
    i32.const 8
    local.set 3
    local.get 3
    call $summ_new_sym_var
    local.set 4
    local.get 2
    local.get 4
    i32.store offset=12
    local.get 2
    i32.load offset=12
    local.set 5
    i32.const 24
    local.set 6
    local.get 5
    local.get 6
    i32.shl
    local.set 7
    local.get 7
    local.get 6
    i32.shr_s
    local.set 8
    i32.const 16
    local.set 9
    local.get 2
    local.get 9
    i32.add
    local.set 10
    local.get 10
    global.set $__stack_pointer
    local.get 8
    return)
  (func $malloc (type 1) (param i32) (result i32)
    (local i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32)
    global.get $__stack_pointer
    local.set 1
    i32.const 16
    local.set 2
    local.get 1
    local.get 2
    i32.sub
    local.set 3
    local.get 3
    global.set $__stack_pointer
    local.get 3
    local.get 0
    i32.store offset=12
    i32.const 0
    local.set 4
    local.get 4
    i32.load offset=1056
    local.set 5
    local.get 3
    local.get 5
    i32.store offset=8
    local.get 3
    i32.load offset=12
    local.set 6
    i32.const 0
    local.set 7
    local.get 7
    i32.load offset=1056
    local.set 8
    local.get 8
    local.get 6
    i32.add
    local.set 9
    i32.const 0
    local.set 10
    local.get 10
    local.get 9
    i32.store offset=1056
    local.get 3
    i32.load offset=8
    local.set 11
    local.get 3
    i32.load offset=12
    local.set 12
    local.get 11
    local.get 12
    call $__WASP_alloc
    local.set 13
    i32.const 16
    local.set 14
    local.get 3
    local.get 14
    i32.add
    local.set 15
    local.get 15
    global.set $__stack_pointer
    local.get 13
    return)
  (func $calloc (type 4) (param i32 i32) (result i32)
    (local i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32)
    global.get $__stack_pointer
    local.set 2
    i32.const 16
    local.set 3
    local.get 2
    local.get 3
    i32.sub
    local.set 4
    local.get 4
    global.set $__stack_pointer
    local.get 4
    local.get 0
    i32.store offset=12
    local.get 4
    local.get 1
    i32.store offset=8
    i32.const 0
    local.set 5
    local.get 5
    i32.load offset=1056
    local.set 6
    local.get 4
    local.get 6
    i32.store offset=4
    local.get 4
    i32.load offset=12
    local.set 7
    local.get 4
    i32.load offset=8
    local.set 8
    local.get 7
    local.get 8
    i32.mul
    local.set 9
    i32.const 0
    local.set 10
    local.get 10
    i32.load offset=1056
    local.set 11
    local.get 11
    local.get 9
    i32.add
    local.set 12
    i32.const 0
    local.set 13
    local.get 13
    local.get 12
    i32.store offset=1056
    local.get 4
    i32.load offset=4
    local.set 14
    local.get 4
    i32.load offset=12
    local.set 15
    local.get 4
    i32.load offset=8
    local.set 16
    local.get 15
    local.get 16
    i32.mul
    local.set 17
    local.get 14
    local.get 17
    call $__WASP_alloc
    local.set 18
    i32.const 16
    local.set 19
    local.get 4
    local.get 19
    i32.add
    local.set 20
    local.get 20
    global.set $__stack_pointer
    local.get 18
    return)
  (func $realloc (type 4) (param i32 i32) (result i32)
    (local i32 i32 i32 i32 i32 i32 i32 i32 i32)
    global.get $__stack_pointer
    local.set 2
    i32.const 16
    local.set 3
    local.get 2
    local.get 3
    i32.sub
    local.set 4
    local.get 4
    global.set $__stack_pointer
    local.get 4
    local.get 0
    i32.store offset=12
    local.get 4
    local.get 1
    i32.store offset=8
    local.get 4
    i32.load offset=12
    local.set 5
    local.get 5
    call $__WASP_dealloc
    local.get 4
    i32.load offset=12
    local.set 6
    local.get 4
    i32.load offset=8
    local.set 7
    local.get 6
    local.get 7
    call $__WASP_alloc
    local.set 8
    i32.const 16
    local.set 9
    local.get 4
    local.get 9
    i32.add
    local.set 10
    local.get 10
    global.set $__stack_pointer
    local.get 8
    return)
  (func $free (type 2) (param i32)
    (local i32 i32 i32 i32 i32 i32)
    global.get $__stack_pointer
    local.set 1
    i32.const 16
    local.set 2
    local.get 1
    local.get 2
    i32.sub
    local.set 3
    local.get 3
    global.set $__stack_pointer
    local.get 3
    local.get 0
    i32.store offset=12
    local.get 3
    i32.load offset=12
    local.set 4
    local.get 4
    call $__WASP_dealloc
    i32.const 16
    local.set 5
    local.get 3
    local.get 5
    i32.add
    local.set 6
    local.get 6
    global.set $__stack_pointer
    return)
  (func $getchar (type 0) (result i32)
    (local i32 i32 i32 i32 i32 i32)
    i32.const 0
    local.set 0
    local.get 0
    i32.load offset=1060
    local.set 1
    local.get 1
    call_indirect (type 0)
    local.set 2
    i32.const 24
    local.set 3
    local.get 2
    local.get 3
    i32.shl
    local.set 4
    local.get 4
    local.get 3
    i32.shr_s
    local.set 5
    local.get 5
    return)
  (func $__WASP_alloc (type 4) (param i32 i32) (result i32)
    (local i32 i32 i32 i32)
    global.get $__stack_pointer
    local.set 2
    i32.const 16
    local.set 3
    local.get 2
    local.get 3
    i32.sub
    local.set 4
    local.get 4
    local.get 0
    i32.store offset=12
    local.get 4
    local.get 1
    i32.store offset=8
    local.get 4
    i32.load offset=12
    local.set 5
    local.get 5
    return)
  (func $__WASP_dealloc (type 2) (param i32)
    (local i32 i32 i32)
    global.get $__stack_pointer
    local.set 1
    i32.const 16
    local.set 2
    local.get 1
    local.get 2
    i32.sub
    local.set 3
    local.get 3
    local.get 0
    i32.store offset=12
    return)
  (func $__WASP_symb_int (type 1) (param i32) (result i32)
    (local i32 i32 i32 i32)
    global.get $__stack_pointer
    local.set 1
    i32.const 16
    local.set 2
    local.get 1
    local.get 2
    i32.sub
    local.set 3
    local.get 3
    local.get 0
    i32.store offset=12
    i32.const 0
    local.set 4
    local.get 4
    return)
  (func $__WASP_symb_long (type 5) (param i32) (result i64)
    (local i32 i32 i32 i64)
    global.get $__stack_pointer
    local.set 1
    i32.const 16
    local.set 2
    local.get 1
    local.get 2
    i32.sub
    local.set 3
    local.get 3
    local.get 0
    i32.store offset=12
    i64.const 0
    local.set 4
    local.get 4
    return)
  (table (;0;) 2 2 funcref)
  (memory (;0;) 2)
  (global $__stack_pointer (mut i32) (i32.const 66608))
  (export "memory" (memory 0))
  (export "__original_main" (func $__original_main))
  (elem (;0;) (i32.const 1) func $getchar1)
  (data $.rodata (i32.const 1024) "i\00%d\00c\00sym_i64\00sym_i32\00%d \00%d\0a\00")
  (data $.data (i32.const 1056) "0\04\01\00\01\00\00\00"))
