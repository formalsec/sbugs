(module
  (type (;0;) (func (result i32)))
  (type (;1;) (func (param i32 i32) (result i32)))
  (type (;2;) (func (param i32)))
  (type (;3;) (func (param i32) (result i32)))
  (func $__original_main (type 0) (result i32)
    (local i32 i32)
    global.get $__stack_pointer
    i32.const 64
    i32.sub
    local.tee 0
    global.set $__stack_pointer
    local.get 0
    i32.const 1034
    call $__WASP_symb_int
    i32.store offset=48
    local.get 0
    local.get 0
    i32.load offset=48
    i32.const -1
    i32.add
    i32.store offset=48
    local.get 0
    i32.const 1031
    call $__WASP_symb_int
    i32.store offset=44
    local.get 0
    local.get 0
    i32.load offset=44
    i32.const -1
    i32.add
    i32.store offset=44
    local.get 0
    i32.const 1027
    call $__WASP_symb_int
    i32.store offset=56
    local.get 0
    i32.const 1029
    call $__WASP_symb_int
    i32.store offset=52
    i32.const 0
    local.get 0
    i32.load offset=56
    i32.const 4
    call $calloc
    i32.store offset=1052
    local.get 0
    local.get 0
    i32.load offset=52
    i32.const 8
    call $calloc
    i32.store offset=36
    i32.const 0
    local.get 0
    i32.load offset=56
    i32.const 4
    call $calloc
    i32.store offset=1056
    local.get 0
    i32.const 0
    i32.store offset=60
    block  ;; label = @1
      loop  ;; label = @2
        local.get 0
        i32.load offset=60
        local.get 0
        i32.load offset=52
        i32.lt_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        i32.const 1024
        call $__WASP_symb_int
        local.set 1
        local.get 0
        i32.load offset=36
        local.get 0
        i32.load offset=60
        i32.const 3
        i32.shl
        i32.add
        local.get 1
        i32.store
        local.get 0
        i32.load offset=36
        local.get 0
        i32.load offset=60
        i32.const 3
        i32.shl
        i32.add
        local.tee 1
        local.get 1
        i32.load
        i32.const -1
        i32.add
        i32.store
        local.get 0
        i32.const 1026
        call $__WASP_symb_int
        i32.store offset=32
        local.get 0
        local.get 0
        i32.load offset=32
        i32.const -1
        i32.add
        i32.store offset=32
        local.get 0
        i32.load offset=36
        local.get 0
        i32.load offset=60
        i32.const 3
        i32.shl
        i32.add
        i32.const 0
        i32.load offset=1052
        local.get 0
        i32.load offset=32
        i32.const 2
        i32.shl
        i32.add
        i32.load
        i32.store offset=4
        i32.const 0
        i32.load offset=1052
        local.get 0
        i32.load offset=32
        i32.const 2
        i32.shl
        i32.add
        local.get 0
        i32.load offset=36
        local.get 0
        i32.load offset=60
        i32.const 3
        i32.shl
        i32.add
        i32.store
        local.get 0
        local.get 0
        i32.load offset=60
        i32.const 1
        i32.add
        i32.store offset=60
        br 0 (;@2;)
      end
    end
    local.get 0
    i32.const 1
    i32.store offset=28
    local.get 0
    i32.const 0
    i32.store offset=60
    loop  ;; label = @1
      i32.const 0
      local.set 1
      block  ;; label = @2
        local.get 0
        i32.load offset=28
        i32.eqz
        br_if 0 (;@2;)
        local.get 0
        i32.load offset=60
        local.get 0
        i32.load offset=56
        i32.lt_s
        local.set 1
      end
      block  ;; label = @2
        local.get 1
        i32.const 1
        i32.and
        i32.eqz
        br_if 0 (;@2;)
        local.get 0
        i32.const 0
        i32.const 0
        i32.load offset=1052
        local.get 0
        i32.load offset=60
        i32.const 2
        i32.shl
        i32.add
        i32.load
        i32.eq
        i32.const 1
        i32.and
        i32.store offset=28
        i32.const 1
        local.set 1
        block  ;; label = @3
          local.get 0
          i32.load offset=28
          br_if 0 (;@3;)
          block  ;; label = @4
            block  ;; label = @5
              i32.const 0
              i32.load offset=1052
              local.get 0
              i32.load offset=60
              i32.const 2
              i32.shl
              i32.add
              i32.load
              i32.const 0
              i32.ne
              i32.const 1
              i32.and
              i32.eqz
              br_if 0 (;@5;)
              i32.const 0
              i32.load offset=1052
              local.get 0
              i32.load offset=60
              i32.const 2
              i32.shl
              i32.add
              i32.load
              i32.load offset=4
              local.set 1
              br 1 (;@4;)
            end
            i32.const 0
            local.set 1
          end
          i32.const 0
          local.get 1
          i32.eq
          local.set 1
        end
        local.get 0
        local.get 1
        i32.const 1
        i32.and
        i32.store offset=28
        i32.const 1
        local.set 1
        block  ;; label = @3
          local.get 0
          i32.load offset=28
          br_if 0 (;@3;)
          block  ;; label = @4
            block  ;; label = @5
              i32.const 0
              i32.load offset=1052
              local.get 0
              i32.load offset=60
              i32.const 2
              i32.shl
              i32.add
              i32.load
              i32.load offset=4
              i32.const 0
              i32.ne
              i32.const 1
              i32.and
              i32.eqz
              br_if 0 (;@5;)
              i32.const 0
              i32.load offset=1052
              local.get 0
              i32.load offset=60
              i32.const 2
              i32.shl
              i32.add
              i32.load
              i32.load offset=4
              i32.load offset=4
              local.set 1
              br 1 (;@4;)
            end
            i32.const 0
            local.set 1
          end
          i32.const 0
          local.get 1
          i32.eq
          local.set 1
        end
        local.get 0
        local.get 1
        i32.const 1
        i32.and
        i32.store offset=28
        local.get 0
        local.get 0
        i32.load offset=60
        i32.const 1
        i32.add
        i32.store offset=60
        br 1 (;@1;)
      end
    end
    local.get 0
    i32.const 0
    i32.store offset=60
    loop  ;; label = @1
      i32.const 0
      local.set 1
      block  ;; label = @2
        local.get 0
        i32.load offset=28
        i32.eqz
        br_if 0 (;@2;)
        local.get 0
        i32.load offset=60
        local.get 0
        i32.load offset=56
        i32.lt_s
        local.set 1
      end
      block  ;; label = @2
        local.get 1
        i32.const 1
        i32.and
        i32.eqz
        br_if 0 (;@2;)
        local.get 0
        local.get 0
        i32.load offset=60
        i32.const 2
        call $DFS_visit
        i32.store offset=28
        local.get 0
        local.get 0
        i32.load offset=60
        i32.const 1
        i32.add
        i32.store offset=60
        br 1 (;@1;)
      end
    end
    block  ;; label = @1
      block  ;; label = @2
        local.get 0
        i32.load offset=28
        i32.eqz
        br_if 0 (;@2;)
        local.get 0
        i32.load offset=48
        i32.const 4
        call $DFS_visit
        drop
        local.get 0
        i32.load offset=44
        i32.const 8
        call $DFS_visit
        drop
        local.get 0
        local.get 0
        i32.load offset=56
        i32.const 4
        call $calloc
        i32.store offset=40
        local.get 0
        i32.const 0
        i32.store offset=60
        block  ;; label = @3
          loop  ;; label = @4
            local.get 0
            i32.load offset=60
            local.get 0
            i32.load offset=56
            i32.lt_s
            i32.const 1
            i32.and
            i32.eqz
            br_if 1 (;@3;)
            local.get 0
            i32.const 0
            i32.load offset=1052
            local.get 0
            i32.load offset=60
            i32.const 2
            i32.shl
            i32.add
            i32.load
            i32.store offset=24
            block  ;; label = @5
              loop  ;; label = @6
                i32.const 0
                local.get 0
                i32.load offset=24
                i32.ne
                i32.const 1
                i32.and
                i32.eqz
                br_if 1 (;@5;)
                local.get 0
                local.get 0
                i32.load offset=24
                i32.load offset=4
                i32.store offset=20
                local.get 0
                i32.load offset=24
                local.get 0
                i32.load offset=40
                local.get 0
                i32.load offset=24
                i32.load
                i32.const 2
                i32.shl
                i32.add
                i32.load
                i32.store offset=4
                local.get 0
                i32.load offset=40
                local.get 0
                i32.load offset=24
                i32.load
                i32.const 2
                i32.shl
                i32.add
                local.get 0
                i32.load offset=24
                i32.store
                local.get 0
                i32.load offset=24
                local.get 0
                i32.load offset=60
                i32.store
                local.get 0
                local.get 0
                i32.load offset=20
                i32.store offset=24
                br 0 (;@6;)
              end
            end
            local.get 0
            local.get 0
            i32.load offset=60
            i32.const 1
            i32.add
            i32.store offset=60
            br 0 (;@4;)
          end
        end
        local.get 0
        i32.const 0
        i32.store offset=16
        local.get 0
        i32.const 0
        i32.store offset=60
        block  ;; label = @3
          loop  ;; label = @4
            local.get 0
            i32.load offset=60
            local.get 0
            i32.load offset=56
            i32.lt_s
            i32.const 1
            i32.and
            i32.eqz
            br_if 1 (;@3;)
            block  ;; label = @5
              i32.const 4
              i32.const 0
              i32.load offset=1056
              local.get 0
              i32.load offset=60
              i32.const 2
              i32.shl
              i32.add
              i32.load
              i32.const 4
              i32.and
              i32.eq
              i32.const 1
              i32.and
              i32.eqz
              br_if 0 (;@5;)
              i32.const 8
              i32.const 0
              i32.load offset=1056
              local.get 0
              i32.load offset=60
              i32.const 2
              i32.shl
              i32.add
              i32.load
              i32.const 8
              i32.and
              i32.eq
              i32.const 1
              i32.and
              i32.eqz
              br_if 0 (;@5;)
              local.get 0
              i32.const 1
              i32.store offset=12
              local.get 0
              local.get 0
              i32.load offset=40
              local.get 0
              i32.load offset=60
              i32.const 2
              i32.shl
              i32.add
              i32.load
              i32.store offset=24
              loop  ;; label = @6
                i32.const 0
                local.set 1
                block  ;; label = @7
                  local.get 0
                  i32.load offset=12
                  i32.eqz
                  br_if 0 (;@7;)
                  i32.const 0
                  local.get 0
                  i32.load offset=24
                  i32.ne
                  local.set 1
                end
                block  ;; label = @7
                  local.get 1
                  i32.const 1
                  i32.and
                  i32.eqz
                  br_if 0 (;@7;)
                  i32.const 1
                  local.set 1
                  block  ;; label = @8
                    i32.const 4
                    i32.const 0
                    i32.load offset=1056
                    local.get 0
                    i32.load offset=24
                    i32.load
                    i32.const 2
                    i32.shl
                    i32.add
                    i32.load
                    i32.const 4
                    i32.and
                    i32.ne
                    i32.const 1
                    i32.and
                    br_if 0 (;@8;)
                    i32.const 8
                    i32.const 0
                    i32.load offset=1056
                    local.get 0
                    i32.load offset=24
                    i32.load
                    i32.const 2
                    i32.shl
                    i32.add
                    i32.load
                    i32.const 8
                    i32.and
                    i32.ne
                    local.set 1
                  end
                  local.get 0
                  local.get 1
                  i32.const 1
                  i32.and
                  i32.store offset=12
                  local.get 0
                  local.get 0
                  i32.load offset=24
                  i32.load offset=4
                  i32.store offset=24
                  br 1 (;@6;)
                end
              end
              block  ;; label = @6
                local.get 0
                i32.load offset=12
                i32.eqz
                br_if 0 (;@6;)
                local.get 0
                local.get 0
                i32.load offset=60
                i32.const 1
                i32.add
                i32.store
                i32.const 1039
                local.get 0
                call $printf
                drop
                local.get 0
                local.get 0
                i32.load offset=16
                i32.const 1
                i32.add
                i32.store offset=16
              end
            end
            local.get 0
            local.get 0
            i32.load offset=60
            i32.const 1
            i32.add
            i32.store offset=60
            br 0 (;@4;)
          end
        end
        block  ;; label = @3
          i32.const 0
          local.get 0
          i32.load offset=16
          i32.eq
          i32.const 1
          i32.and
          i32.eqz
          br_if 0 (;@3;)
          i32.const 1037
          i32.const 0
          call $printf
          drop
        end
        i32.const 1044
        i32.const 0
        call $printf
        drop
        local.get 0
        i32.load offset=40
        call $free
        br 1 (;@1;)
      end
      i32.const 1043
      i32.const 0
      call $printf
      drop
    end
    i32.const 0
    i32.load offset=1056
    call $free
    local.get 0
    i32.load offset=36
    call $free
    i32.const 0
    i32.load offset=1052
    call $free
    local.get 0
    i32.const 64
    i32.add
    global.set $__stack_pointer
    i32.const 0)
  (func $DFS_visit (type 1) (param i32 i32) (result i32)
    (local i32)
    global.get $__stack_pointer
    i32.const 16
    i32.sub
    local.tee 2
    global.set $__stack_pointer
    local.get 2
    local.get 0
    i32.store offset=12
    local.get 2
    local.get 1
    i32.store offset=8
    local.get 2
    i32.const 1
    i32.store offset=4
    block  ;; label = @1
      i32.const 0
      local.get 2
      i32.load offset=8
      i32.const 0
      i32.load offset=1056
      local.get 2
      i32.load offset=12
      i32.const 2
      i32.shl
      i32.add
      i32.load
      i32.and
      i32.eq
      i32.const 1
      i32.and
      i32.eqz
      br_if 0 (;@1;)
      i32.const 0
      i32.load offset=1056
      local.get 2
      i32.load offset=12
      i32.const 2
      i32.shl
      i32.add
      local.tee 0
      local.get 0
      i32.load
      local.get 2
      i32.load offset=8
      i32.or
      i32.store
      local.get 2
      i32.const 0
      i32.load offset=1052
      local.get 2
      i32.load offset=12
      i32.const 2
      i32.shl
      i32.add
      i32.load
      i32.store
      loop  ;; label = @2
        i32.const 0
        local.set 0
        block  ;; label = @3
          local.get 2
          i32.load offset=4
          i32.eqz
          br_if 0 (;@3;)
          i32.const 0
          local.get 2
          i32.load
          i32.ne
          local.set 0
        end
        block  ;; label = @3
          local.get 0
          i32.const 1
          i32.and
          i32.eqz
          br_if 0 (;@3;)
          local.get 2
          local.get 2
          i32.load
          i32.load
          local.get 2
          i32.load offset=8
          call $DFS_visit
          i32.store offset=4
          i32.const 0
          local.set 0
          block  ;; label = @4
            local.get 2
            i32.load offset=4
            i32.eqz
            br_if 0 (;@4;)
            i32.const 1
            i32.const 0
            i32.load offset=1056
            local.get 2
            i32.load
            i32.load
            i32.const 2
            i32.shl
            i32.add
            i32.load
            i32.const 1
            i32.and
            i32.eq
            local.set 0
          end
          local.get 2
          local.get 0
          i32.const 1
          i32.and
          i32.store offset=4
          local.get 2
          local.get 2
          i32.load
          i32.load offset=4
          i32.store
          br 1 (;@2;)
        end
      end
      i32.const 0
      i32.load offset=1056
      local.get 2
      i32.load offset=12
      i32.const 2
      i32.shl
      i32.add
      local.tee 0
      local.get 0
      i32.load
      i32.const 1
      i32.or
      i32.store
    end
    local.get 2
    i32.load offset=4
    local.set 0
    local.get 2
    i32.const 16
    i32.add
    global.set $__stack_pointer
    local.get 0)
  (func $printf (type 1) (param i32 i32) (result i32)
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
  (func $calloc (type 1) (param i32 i32) (result i32)
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
    i32.load offset=1048
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
    i32.load offset=1048
    local.set 11
    local.get 11
    local.get 9
    i32.add
    local.set 12
    i32.const 0
    local.set 13
    local.get 13
    local.get 12
    i32.store offset=1048
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
  (func $__WASP_alloc (type 1) (param i32 i32) (result i32)
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
  (func $__WASP_symb_int (type 3) (param i32) (result i32)
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
  (table (;0;) 1 1 funcref)
  (memory (;0;) 2)
  (global $__stack_pointer (mut i32) (i32.const 66608))
  (export "memory" (memory 0))
  (export "__original_main" (func $__original_main))
  (data $.rodata (i32.const 1024) "v\00in\00m\00qb\00qa\00-\00%d \000\0a\00")
  (data $.data (i32.const 1048) "0\04\01\00"))
