(module
  (type (;0;) (func (param i32 i32) (result i32)))
  (type (;1;) (func (param i32) (result i32)))
  (type (;2;) (func (result i32)))
  (type (;3;) (func (param i32)))
  (type (;4;) (func (param i32 i32 i32 i32)))
  (type (;5;) (func (param i32 i32 i32 i32 i32)))
  (func $dfs (type 0) (param i32 i32) (result i32)
    (local i32)
    global.get 0
    i32.const 32
    i32.sub
    local.tee 2
    global.set 0
    local.get 2
    local.get 0
    i32.store offset=28
    local.get 2
    local.get 1
    i32.store offset=24
    i32.const 0
    i32.load offset=1044
    local.get 2
    i32.load offset=24
    i32.const 2
    i32.shl
    i32.add
    i32.const 1
    i32.store
    i32.const 0
    i32.load offset=1052
    local.get 2
    i32.load offset=24
    i32.const 2
    i32.shl
    i32.add
    i32.const 0
    i32.load offset=1048
    i32.store
    i32.const 0
    i32.load offset=1056
    local.get 2
    i32.load offset=24
    i32.const 2
    i32.shl
    i32.add
    i32.const 0
    i32.load offset=1048
    i32.store
    i32.const 0
    i32.const 0
    i32.load offset=1048
    i32.const 1
    i32.add
    i32.store offset=1048
    local.get 2
    local.get 2
    i32.load offset=24
    i32.store offset=20
    local.get 2
    i32.const 0
    i32.store offset=16
    local.get 2
    i32.const 0
    i32.store offset=12
    local.get 2
    i32.const 0
    i32.load offset=1060
    local.get 2
    i32.load offset=24
    i32.const 2
    i32.shl
    i32.add
    i32.load
    i32.store offset=8
    block  ;; label = @1
      loop  ;; label = @2
        i32.const 0
        local.get 2
        i32.load offset=8
        i32.ne
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        block  ;; label = @3
          block  ;; label = @4
            i32.const 0
            i32.const 0
            i32.load offset=1044
            local.get 2
            i32.load offset=8
            i32.load
            i32.const 2
            i32.shl
            i32.add
            i32.load
            i32.eq
            i32.const 1
            i32.and
            i32.eqz
            br_if 0 (;@4;)
            local.get 2
            local.get 2
            i32.load offset=16
            i32.const 1
            i32.add
            i32.store offset=16
            local.get 2
            local.get 2
            i32.load offset=24
            local.get 2
            i32.load offset=8
            i32.load
            call $dfs
            i32.store offset=4
            block  ;; label = @5
              local.get 2
              i32.load offset=4
              local.get 2
              i32.load offset=20
              i32.gt_s
              i32.const 1
              i32.and
              i32.eqz
              br_if 0 (;@5;)
              local.get 2
              local.get 2
              i32.load offset=4
              i32.store offset=20
            end
            block  ;; label = @5
              i32.const 0
              i32.load offset=1056
              local.get 2
              i32.load offset=8
              i32.load
              i32.const 2
              i32.shl
              i32.add
              i32.load
              i32.const 0
              i32.load offset=1056
              local.get 2
              i32.load offset=24
              i32.const 2
              i32.shl
              i32.add
              i32.load
              i32.lt_s
              i32.const 1
              i32.and
              i32.eqz
              br_if 0 (;@5;)
              i32.const 0
              i32.load offset=1056
              local.get 2
              i32.load offset=24
              i32.const 2
              i32.shl
              i32.add
              i32.const 0
              i32.load offset=1056
              local.get 2
              i32.load offset=8
              i32.load
              i32.const 2
              i32.shl
              i32.add
              i32.load
              i32.store
            end
            block  ;; label = @5
              i32.const -1
              local.get 2
              i32.load offset=28
              i32.ne
              i32.const 1
              i32.and
              i32.eqz
              br_if 0 (;@5;)
              i32.const 0
              i32.load offset=1056
              local.get 2
              i32.load offset=8
              i32.load
              i32.const 2
              i32.shl
              i32.add
              i32.load
              i32.const 0
              i32.load offset=1052
              local.get 2
              i32.load offset=24
              i32.const 2
              i32.shl
              i32.add
              i32.load
              i32.ge_s
              i32.const 1
              i32.and
              i32.eqz
              br_if 0 (;@5;)
              local.get 2
              i32.const 1
              i32.store offset=12
            end
            br 1 (;@3;)
          end
          block  ;; label = @4
            local.get 2
            i32.load offset=8
            i32.load
            local.get 2
            i32.load offset=28
            i32.ne
            i32.const 1
            i32.and
            i32.eqz
            br_if 0 (;@4;)
            i32.const 0
            i32.load offset=1052
            local.get 2
            i32.load offset=8
            i32.load
            i32.const 2
            i32.shl
            i32.add
            i32.load
            i32.const 0
            i32.load offset=1056
            local.get 2
            i32.load offset=24
            i32.const 2
            i32.shl
            i32.add
            i32.load
            i32.lt_s
            i32.const 1
            i32.and
            i32.eqz
            br_if 0 (;@4;)
            i32.const 0
            i32.load offset=1056
            local.get 2
            i32.load offset=24
            i32.const 2
            i32.shl
            i32.add
            i32.const 0
            i32.load offset=1052
            local.get 2
            i32.load offset=8
            i32.load
            i32.const 2
            i32.shl
            i32.add
            i32.load
            i32.store
          end
        end
        local.get 2
        local.get 2
        i32.load offset=8
        i32.load offset=4
        i32.store offset=8
        br 0 (;@2;)
      end
    end
    block  ;; label = @1
      i32.const -1
      local.get 2
      i32.load offset=28
      i32.eq
      i32.const 1
      i32.and
      i32.eqz
      br_if 0 (;@1;)
      i32.const 1
      local.get 2
      i32.load offset=16
      i32.lt_s
      i32.const 1
      i32.and
      i32.eqz
      br_if 0 (;@1;)
      local.get 2
      i32.const 1
      i32.store offset=12
    end
    block  ;; label = @1
      i32.const 1
      local.get 2
      i32.load offset=12
      i32.eq
      i32.const 1
      i32.and
      i32.eqz
      br_if 0 (;@1;)
      i32.const 0
      i32.load offset=1064
      i32.const 0
      i32.load offset=1068
      i32.const 2
      i32.shl
      i32.add
      local.get 2
      i32.load offset=24
      i32.store
      i32.const 0
      i32.load offset=1072
      local.get 2
      i32.load offset=24
      i32.const 2
      i32.shl
      i32.add
      i32.const 1
      i32.store
      i32.const 0
      i32.const 0
      i32.load offset=1068
      i32.const 1
      i32.add
      i32.store offset=1068
    end
    local.get 2
    i32.load offset=20
    local.set 0
    local.get 2
    i32.const 32
    i32.add
    global.set 0
    local.get 0)
  (func $RtDfs (type 1) (param i32) (result i32)
    (local i32)
    global.get 0
    i32.const 16
    i32.sub
    local.tee 1
    global.set 0
    local.get 1
    local.get 0
    i32.store offset=12
    i32.const 0
    i32.load offset=1044
    local.get 1
    i32.load offset=12
    i32.const 2
    i32.shl
    i32.add
    i32.const 1
    i32.store
    local.get 1
    i32.const 1
    i32.store offset=8
    local.get 1
    i32.const 0
    i32.load offset=1060
    local.get 1
    i32.load offset=12
    i32.const 2
    i32.shl
    i32.add
    i32.load
    i32.store offset=4
    block  ;; label = @1
      loop  ;; label = @2
        i32.const 0
        local.get 1
        i32.load offset=4
        i32.ne
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        block  ;; label = @3
          i32.const 0
          i32.const 0
          i32.load offset=1072
          local.get 1
          i32.load offset=4
          i32.load
          i32.const 2
          i32.shl
          i32.add
          i32.load
          i32.eq
          i32.const 1
          i32.and
          i32.eqz
          br_if 0 (;@3;)
          i32.const 0
          i32.const 0
          i32.load offset=1044
          local.get 1
          i32.load offset=4
          i32.load
          i32.const 2
          i32.shl
          i32.add
          i32.load
          i32.eq
          i32.const 1
          i32.and
          i32.eqz
          br_if 0 (;@3;)
          local.get 1
          local.get 1
          i32.load offset=4
          i32.load
          call $RtDfs
          local.get 1
          i32.load offset=8
          i32.add
          i32.store offset=8
        end
        local.get 1
        local.get 1
        i32.load offset=4
        i32.load offset=4
        i32.store offset=4
        br 0 (;@2;)
      end
    end
    local.get 1
    i32.load offset=8
    local.set 0
    local.get 1
    i32.const 16
    i32.add
    global.set 0
    local.get 0)
  (func $__original_main (type 2) (result i32)
    (local i32 i32 i32)
    global.get 0
    i32.const 112
    i32.sub
    local.tee 0
    global.set 0
    i32.const 0
    i32.const 1024
    i32.symbolic
    i32.store offset=1076
    i32.const 0
    i32.const 0
    i32.load offset=1076
    i32.const 2
    i32.shl
    call $malloc
    i32.store offset=1052
    i32.const 0
    i32.const 0
    i32.load offset=1076
    i32.const 2
    i32.shl
    call $malloc
    i32.store offset=1056
    i32.const 0
    i32.const 0
    i32.load offset=1076
    i32.const 2
    i32.shl
    call $malloc
    i32.store offset=1064
    i32.const 0
    i32.const 0
    i32.load offset=1076
    i32.const 4
    call $calloc
    i32.store offset=1072
    local.get 0
    i32.const 0
    i32.load offset=1076
    i32.const 2
    i32.shl
    call $malloc
    i32.store offset=108
    i32.const 0
    i32.const 0
    i32.load offset=1076
    i32.const 4
    call $calloc
    i32.store offset=1044
    i32.const 0
    i32.const 0
    i32.load offset=1076
    i32.const 4
    call $calloc
    i32.store offset=1060
    i32.const 0
    i32.const 1028
    i32.symbolic
    i32.store offset=1080
    local.get 0
    i32.const 0
    i32.store offset=104
    block  ;; label = @1
      loop  ;; label = @2
        local.get 0
        i32.load offset=104
        i32.const 0
        i32.load offset=1080
        i32.lt_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        local.get 0
        i32.const 1026
        i32.symbolic
        i32.store offset=100
        local.get 0
        local.get 0
        i32.load offset=100
        i32.const -1
        i32.add
        i32.store offset=100
        local.get 0
        i32.const 1024
        i32.symbolic
        i32.store offset=96
        local.get 0
        local.get 0
        i32.load offset=96
        i32.const -1
        i32.add
        i32.store offset=96
        local.get 0
        i32.const 8
        call $malloc
        i32.store offset=92
        local.get 0
        i32.load offset=92
        local.get 0
        i32.load offset=96
        i32.store
        local.get 0
        i32.load offset=92
        i32.const 0
        i32.load offset=1060
        local.get 0
        i32.load offset=100
        i32.const 2
        i32.shl
        i32.add
        i32.load
        i32.store offset=4
        i32.const 0
        i32.load offset=1060
        local.get 0
        i32.load offset=100
        i32.const 2
        i32.shl
        i32.add
        local.get 0
        i32.load offset=92
        i32.store
        local.get 0
        i32.const 8
        call $malloc
        i32.store offset=92
        local.get 0
        i32.load offset=92
        local.get 0
        i32.load offset=100
        i32.store
        local.get 0
        i32.load offset=92
        i32.const 0
        i32.load offset=1060
        local.get 0
        i32.load offset=96
        i32.const 2
        i32.shl
        i32.add
        i32.load
        i32.store offset=4
        i32.const 0
        i32.load offset=1060
        local.get 0
        i32.load offset=96
        i32.const 2
        i32.shl
        i32.add
        local.get 0
        i32.load offset=92
        i32.store
        local.get 0
        local.get 0
        i32.load offset=104
        i32.const 1
        i32.add
        i32.store offset=104
        br 0 (;@2;)
      end
    end
    i32.const 0
    i32.const 0
    i32.store offset=1048
    i32.const 0
    i32.const 0
    i32.store offset=1068
    local.get 0
    i32.const 0
    i32.store offset=88
    local.get 0
    i32.const 0
    i32.store offset=104
    block  ;; label = @1
      loop  ;; label = @2
        local.get 0
        i32.load offset=104
        i32.const 0
        i32.load offset=1076
        i32.lt_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        block  ;; label = @3
          i32.const 0
          i32.const 0
          i32.load offset=1044
          local.get 0
          i32.load offset=104
          i32.const 2
          i32.shl
          i32.add
          i32.load
          i32.eq
          i32.const 1
          i32.and
          i32.eqz
          br_if 0 (;@3;)
          i32.const -1
          local.get 0
          i32.load offset=104
          call $dfs
          local.set 1
          local.get 0
          i32.load offset=108
          local.get 0
          i32.load offset=88
          i32.const 2
          i32.shl
          i32.add
          local.get 1
          i32.store
          local.get 0
          local.get 0
          i32.load offset=88
          i32.const 1
          i32.add
          i32.store offset=88
        end
        local.get 0
        local.get 0
        i32.load offset=104
        i32.const 1
        i32.add
        i32.store offset=104
        br 0 (;@2;)
      end
    end
    local.get 0
    local.get 0
    i32.load offset=88
    i32.store offset=64
    i32.const 1034
    local.get 0
    i32.const 64
    i32.add
    call $printf
    drop
    local.get 0
    i32.load offset=108
    local.get 0
    i32.load offset=88
    i32.const 4
    i32.const 1
    call $qsort
    local.get 0
    i32.const 0
    i32.store offset=104
    block  ;; label = @1
      loop  ;; label = @2
        local.get 0
        i32.load offset=104
        local.get 0
        i32.load offset=88
        i32.const 1
        i32.sub
        i32.lt_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        local.get 0
        local.get 0
        i32.load offset=108
        local.get 0
        i32.load offset=104
        i32.const 2
        i32.shl
        i32.add
        i32.load
        i32.const 1
        i32.add
        i32.store
        i32.const 1030
        local.get 0
        call $printf
        drop
        local.get 0
        local.get 0
        i32.load offset=104
        i32.const 1
        i32.add
        i32.store offset=104
        br 0 (;@2;)
      end
    end
    local.get 0
    local.get 0
    i32.load offset=108
    local.get 0
    i32.load offset=104
    i32.const 2
    i32.shl
    i32.add
    i32.load
    i32.const 1
    i32.add
    i32.store offset=32
    i32.const 1034
    local.get 0
    i32.const 32
    i32.add
    call $printf
    drop
    local.get 0
    i32.const 0
    i32.load offset=1068
    i32.store offset=48
    i32.const 1034
    local.get 0
    i32.const 48
    i32.add
    call $printf
    drop
    local.get 0
    i32.const 0
    i32.store offset=104
    block  ;; label = @1
      loop  ;; label = @2
        local.get 0
        i32.load offset=104
        i32.const 0
        i32.load offset=1076
        i32.lt_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        i32.const 0
        i32.load offset=1044
        local.set 1
        local.get 0
        local.get 0
        i32.load offset=104
        local.tee 2
        i32.const 1
        i32.add
        i32.store offset=104
        local.get 1
        local.get 2
        i32.const 2
        i32.shl
        i32.add
        i32.const 0
        i32.store
        br 0 (;@2;)
      end
    end
    local.get 0
    i32.const 0
    i32.store offset=84
    local.get 0
    i32.const 0
    i32.store offset=104
    block  ;; label = @1
      loop  ;; label = @2
        local.get 0
        i32.load offset=104
        i32.const 0
        i32.load offset=1076
        i32.lt_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        block  ;; label = @3
          i32.const 0
          i32.const 0
          i32.load offset=1072
          local.get 0
          i32.load offset=104
          i32.const 2
          i32.shl
          i32.add
          i32.load
          i32.eq
          i32.const 1
          i32.and
          i32.eqz
          br_if 0 (;@3;)
          i32.const 0
          i32.const 0
          i32.load offset=1044
          local.get 0
          i32.load offset=104
          i32.const 2
          i32.shl
          i32.add
          i32.load
          i32.eq
          i32.const 1
          i32.and
          i32.eqz
          br_if 0 (;@3;)
          local.get 0
          local.get 0
          i32.load offset=104
          call $RtDfs
          i32.store offset=80
          block  ;; label = @4
            local.get 0
            i32.load offset=80
            local.get 0
            i32.load offset=84
            i32.gt_s
            i32.const 1
            i32.and
            i32.eqz
            br_if 0 (;@4;)
            local.get 0
            local.get 0
            i32.load offset=80
            i32.store offset=84
          end
        end
        local.get 0
        local.get 0
        i32.load offset=104
        i32.const 1
        i32.add
        i32.store offset=104
        br 0 (;@2;)
      end
    end
    local.get 0
    local.get 0
    i32.load offset=84
    i32.store offset=16
    i32.const 1034
    local.get 0
    i32.const 16
    i32.add
    call $printf
    drop
    local.get 0
    i32.const 0
    i32.store offset=104
    block  ;; label = @1
      loop  ;; label = @2
        local.get 0
        i32.load offset=104
        i32.const 0
        i32.load offset=1076
        i32.lt_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        local.get 0
        i32.const 0
        i32.load offset=1060
        local.get 0
        i32.load offset=104
        i32.const 2
        i32.shl
        i32.add
        i32.load
        i32.store offset=76
        block  ;; label = @3
          loop  ;; label = @4
            i32.const 0
            local.get 0
            i32.load offset=76
            i32.ne
            i32.const 1
            i32.and
            i32.eqz
            br_if 1 (;@3;)
            local.get 0
            local.get 0
            i32.load offset=76
            i32.load offset=4
            i32.store offset=72
            local.get 0
            i32.load offset=76
            call $free
            local.get 0
            local.get 0
            i32.load offset=72
            i32.store offset=76
            br 0 (;@4;)
          end
        end
        local.get 0
        local.get 0
        i32.load offset=104
        i32.const 1
        i32.add
        i32.store offset=104
        br 0 (;@2;)
      end
    end
    i32.const 0
    i32.load offset=1052
    call $free
    i32.const 0
    i32.load offset=1056
    call $free
    i32.const 0
    i32.load offset=1064
    call $free
    i32.const 0
    i32.load offset=1072
    call $free
    local.get 0
    i32.load offset=108
    call $free
    i32.const 0
    i32.load offset=1044
    call $free
    i32.const 0
    i32.load offset=1060
    call $free
    local.get 0
    i32.const 112
    i32.add
    global.set 0
    i32.const 0)
  (func $intcmp (type 0) (param i32 i32) (result i32)
    (local i32)
    global.get 0
    i32.const 16
    i32.sub
    local.tee 2
    local.get 0
    i32.store offset=12
    local.get 2
    local.get 1
    i32.store offset=8
    local.get 2
    i32.load offset=12
    i32.load
    local.get 2
    i32.load offset=8
    i32.load
    i32.sub)
  (func $printf (type 0) (param i32 i32) (result i32)
    (local i32 i32 i32 i32)
    global.get 0
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
  (func $malloc (type 1) (param i32) (result i32)
    (local i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32)
    global.get 0
    local.set 1
    i32.const 16
    local.set 2
    local.get 1
    local.get 2
    i32.sub
    local.set 3
    local.get 3
    global.set 0
    local.get 3
    local.get 0
    i32.store offset=12
    i32.const 0
    local.set 4
    local.get 4
    i32.load offset=1040
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
    i32.load offset=1040
    local.set 8
    local.get 8
    local.get 6
    i32.add
    local.set 9
    i32.const 0
    local.set 10
    local.get 10
    local.get 9
    i32.store offset=1040
    local.get 3
    i32.load offset=8
    local.set 11
    local.get 3
    i32.load offset=12
    local.set 12
    local.get 11
    local.get 12
    alloc
    local.set 13
    i32.const 16
    local.set 14
    local.get 3
    local.get 14
    i32.add
    local.set 15
    local.get 15
    global.set 0
    local.get 13
    return)
  (func $calloc (type 0) (param i32 i32) (result i32)
    (local i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32)
    global.get 0
    local.set 2
    i32.const 16
    local.set 3
    local.get 2
    local.get 3
    i32.sub
    local.set 4
    local.get 4
    global.set 0
    local.get 4
    local.get 0
    i32.store offset=12
    local.get 4
    local.get 1
    i32.store offset=8
    i32.const 0
    local.set 5
    local.get 5
    i32.load offset=1040
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
    i32.load offset=1040
    local.set 11
    local.get 11
    local.get 9
    i32.add
    local.set 12
    i32.const 0
    local.set 13
    local.get 13
    local.get 12
    i32.store offset=1040
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
    alloc
    local.set 18
    i32.const 16
    local.set 19
    local.get 4
    local.get 19
    i32.add
    local.set 20
    local.get 20
    global.set 0
    local.get 18
    return)
  (func $free (type 3) (param i32)
    (local i32 i32 i32 i32 i32 i32)
    global.get 0
    local.set 1
    i32.const 16
    local.set 2
    local.get 1
    local.get 2
    i32.sub
    local.set 3
    local.get 3
    global.set 0
    local.get 3
    local.get 0
    i32.store offset=12
    local.get 3
    i32.load offset=12
    local.set 4
    local.get 4
    free
    i32.const 16
    local.set 5
    local.get 3
    local.get 5
    i32.add
    local.set 6
    local.get 6
    global.set 0
    return)
  (func $qsort (type 4) (param i32 i32 i32 i32)
    (local i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32)
    global.get 0
    local.set 4
    i32.const 16
    local.set 5
    local.get 4
    local.get 5
    i32.sub
    local.set 6
    local.get 6
    global.set 0
    local.get 6
    local.get 0
    i32.store offset=12
    local.get 6
    local.get 1
    i32.store offset=8
    local.get 6
    local.get 2
    i32.store offset=4
    local.get 6
    local.get 3
    i32.store
    local.get 6
    i32.load offset=8
    local.set 7
    i32.const 2147483647
    local.set 8
    local.get 7
    local.set 9
    local.get 8
    local.set 10
    local.get 9
    local.get 10
    i32.ge_u
    local.set 11
    i32.const 1
    local.set 12
    local.get 11
    local.get 12
    i32.and
    local.set 13
    block  ;; label = @1
      block  ;; label = @2
        block  ;; label = @3
          local.get 13
          br_if 0 (;@3;)
          local.get 6
          i32.load offset=4
          local.set 14
          i32.const 2147483647
          local.set 15
          local.get 14
          local.set 16
          local.get 15
          local.set 17
          local.get 16
          local.get 17
          i32.ge_u
          local.set 18
          i32.const 1
          local.set 19
          local.get 18
          local.get 19
          i32.and
          local.set 20
          local.get 20
          i32.eqz
          br_if 1 (;@2;)
        end
        br 1 (;@1;)
      end
      local.get 6
      i32.load offset=8
      local.set 21
      i32.const 1
      local.set 22
      local.get 21
      local.set 23
      local.get 22
      local.set 24
      local.get 23
      local.get 24
      i32.gt_u
      local.set 25
      i32.const 1
      local.set 26
      local.get 25
      local.get 26
      i32.and
      local.set 27
      local.get 27
      i32.eqz
      br_if 0 (;@1;)
      local.get 6
      i32.load offset=12
      local.set 28
      local.get 6
      i32.load offset=4
      local.set 29
      local.get 6
      i32.load offset=8
      local.set 30
      i32.const 1
      local.set 31
      local.get 30
      local.get 31
      i32.sub
      local.set 32
      local.get 6
      i32.load
      local.set 33
      i32.const 0
      local.set 34
      local.get 28
      local.get 29
      local.get 34
      local.get 32
      local.get 33
      call $quicksort
    end
    i32.const 16
    local.set 35
    local.get 6
    local.get 35
    i32.add
    local.set 36
    local.get 36
    global.set 0
    return)
  (func $quicksort (type 5) (param i32 i32 i32 i32 i32)
    (local i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32)
    global.get 0
    local.set 5
    i32.const 48
    local.set 6
    local.get 5
    local.get 6
    i32.sub
    local.set 7
    local.get 7
    global.set 0
    local.get 7
    local.get 0
    i32.store offset=44
    local.get 7
    local.get 1
    i32.store offset=40
    local.get 7
    local.get 2
    i32.store offset=36
    local.get 7
    local.get 3
    i32.store offset=32
    local.get 7
    local.get 4
    i32.store offset=28
    local.get 7
    i32.load offset=36
    local.set 8
    i32.const 1
    local.set 9
    local.get 8
    local.get 9
    i32.sub
    local.set 10
    local.get 7
    local.get 10
    i32.store offset=24
    local.get 7
    i32.load offset=32
    local.set 11
    local.get 7
    local.get 11
    i32.store offset=20
    local.get 7
    i32.load offset=36
    local.set 12
    i32.const 1
    local.set 13
    local.get 12
    local.get 13
    i32.sub
    local.set 14
    local.get 7
    local.get 14
    i32.store offset=16
    local.get 7
    i32.load offset=32
    local.set 15
    local.get 7
    local.get 15
    i32.store offset=12
    local.get 7
    i32.load offset=44
    local.set 16
    local.get 7
    i32.load offset=32
    local.set 17
    local.get 7
    i32.load offset=40
    local.set 18
    local.get 17
    local.get 18
    i32.mul
    local.set 19
    local.get 16
    local.get 19
    i32.add
    local.set 20
    local.get 7
    local.get 20
    i32.store offset=4
    local.get 7
    i32.load offset=32
    local.set 21
    local.get 7
    i32.load offset=36
    local.set 22
    local.get 21
    local.set 23
    local.get 22
    local.set 24
    local.get 23
    local.get 24
    i32.le_s
    local.set 25
    i32.const 1
    local.set 26
    local.get 25
    local.get 26
    i32.and
    local.set 27
    block  ;; label = @1
      block  ;; label = @2
        local.get 27
        i32.eqz
        br_if 0 (;@2;)
        br 1 (;@1;)
      end
      local.get 7
      i32.load offset=44
      local.set 28
      local.get 7
      i32.load offset=40
      local.set 29
      local.get 7
      i32.load offset=36
      local.set 30
      local.get 7
      i32.load offset=32
      local.set 31
      local.get 7
      i32.load offset=36
      local.set 32
      local.get 31
      local.get 32
      i32.sub
      local.set 33
      i32.const 2
      local.set 34
      local.get 33
      local.get 34
      i32.div_s
      local.set 35
      local.get 30
      local.get 35
      i32.add
      local.set 36
      local.get 7
      i32.load offset=32
      local.set 37
      local.get 28
      local.get 29
      local.get 36
      local.get 37
      call $exch
      loop  ;; label = @2
        loop  ;; label = @3
          local.get 7
          i32.load offset=24
          local.set 38
          i32.const 1
          local.set 39
          local.get 38
          local.get 39
          i32.add
          local.set 40
          local.get 7
          local.get 40
          i32.store offset=24
          local.get 7
          i32.load offset=32
          local.set 41
          local.get 40
          local.set 42
          local.get 41
          local.set 43
          local.get 42
          local.get 43
          i32.ne
          local.set 44
          i32.const 0
          local.set 45
          i32.const 1
          local.set 46
          local.get 44
          local.get 46
          i32.and
          local.set 47
          local.get 45
          local.set 48
          block  ;; label = @4
            local.get 47
            i32.eqz
            br_if 0 (;@4;)
            local.get 7
            i32.load offset=28
            local.set 49
            local.get 7
            i32.load offset=44
            local.set 50
            local.get 7
            i32.load offset=24
            local.set 51
            local.get 7
            i32.load offset=40
            local.set 52
            local.get 51
            local.get 52
            i32.mul
            local.set 53
            local.get 50
            local.get 53
            i32.add
            local.set 54
            local.get 7
            i32.load offset=4
            local.set 55
            local.get 54
            local.get 55
            local.get 49
            call_indirect (type 0)
            local.set 56
            i32.const 0
            local.set 57
            local.get 56
            local.set 58
            local.get 57
            local.set 59
            local.get 58
            local.get 59
            i32.lt_s
            local.set 60
            local.get 60
            local.set 48
          end
          local.get 48
          local.set 61
          i32.const 1
          local.set 62
          local.get 61
          local.get 62
          i32.and
          local.set 63
          block  ;; label = @4
            local.get 63
            i32.eqz
            br_if 0 (;@4;)
            br 1 (;@3;)
          end
        end
        block  ;; label = @3
          loop  ;; label = @4
            local.get 7
            i32.load offset=28
            local.set 64
            local.get 7
            i32.load offset=4
            local.set 65
            local.get 7
            i32.load offset=44
            local.set 66
            local.get 7
            i32.load offset=20
            local.set 67
            i32.const -1
            local.set 68
            local.get 67
            local.get 68
            i32.add
            local.set 69
            local.get 7
            local.get 69
            i32.store offset=20
            local.get 7
            i32.load offset=40
            local.set 70
            local.get 69
            local.get 70
            i32.mul
            local.set 71
            local.get 66
            local.get 71
            i32.add
            local.set 72
            local.get 65
            local.get 72
            local.get 64
            call_indirect (type 0)
            local.set 73
            i32.const 0
            local.set 74
            local.get 73
            local.set 75
            local.get 74
            local.set 76
            local.get 75
            local.get 76
            i32.lt_s
            local.set 77
            i32.const 1
            local.set 78
            local.get 77
            local.get 78
            i32.and
            local.set 79
            local.get 79
            i32.eqz
            br_if 1 (;@3;)
            local.get 7
            i32.load offset=20
            local.set 80
            local.get 7
            i32.load offset=36
            local.set 81
            local.get 80
            local.set 82
            local.get 81
            local.set 83
            local.get 82
            local.get 83
            i32.eq
            local.set 84
            i32.const 1
            local.set 85
            local.get 84
            local.get 85
            i32.and
            local.set 86
            block  ;; label = @5
              local.get 86
              i32.eqz
              br_if 0 (;@5;)
              br 2 (;@3;)
            end
            br 0 (;@4;)
          end
        end
        local.get 7
        i32.load offset=24
        local.set 87
        local.get 7
        i32.load offset=20
        local.set 88
        local.get 87
        local.set 89
        local.get 88
        local.set 90
        local.get 89
        local.get 90
        i32.ge_s
        local.set 91
        i32.const 1
        local.set 92
        local.get 91
        local.get 92
        i32.and
        local.set 93
        block  ;; label = @3
          block  ;; label = @4
            local.get 93
            i32.eqz
            br_if 0 (;@4;)
            br 1 (;@3;)
          end
          local.get 7
          i32.load offset=44
          local.set 94
          local.get 7
          i32.load offset=40
          local.set 95
          local.get 7
          i32.load offset=24
          local.set 96
          local.get 7
          i32.load offset=20
          local.set 97
          local.get 94
          local.get 95
          local.get 96
          local.get 97
          call $exch
          local.get 7
          i32.load offset=28
          local.set 98
          local.get 7
          i32.load offset=44
          local.set 99
          local.get 7
          i32.load offset=24
          local.set 100
          local.get 7
          i32.load offset=40
          local.set 101
          local.get 100
          local.get 101
          i32.mul
          local.set 102
          local.get 99
          local.get 102
          i32.add
          local.set 103
          local.get 7
          i32.load offset=4
          local.set 104
          local.get 103
          local.get 104
          local.get 98
          call_indirect (type 0)
          local.set 105
          block  ;; label = @4
            local.get 105
            br_if 0 (;@4;)
            local.get 7
            i32.load offset=44
            local.set 106
            local.get 7
            i32.load offset=40
            local.set 107
            local.get 7
            i32.load offset=16
            local.set 108
            i32.const 1
            local.set 109
            local.get 108
            local.get 109
            i32.add
            local.set 110
            local.get 7
            local.get 110
            i32.store offset=16
            local.get 7
            i32.load offset=24
            local.set 111
            local.get 106
            local.get 107
            local.get 110
            local.get 111
            call $exch
          end
          local.get 7
          i32.load offset=28
          local.set 112
          local.get 7
          i32.load offset=4
          local.set 113
          local.get 7
          i32.load offset=44
          local.set 114
          local.get 7
          i32.load offset=20
          local.set 115
          local.get 7
          i32.load offset=40
          local.set 116
          local.get 115
          local.get 116
          i32.mul
          local.set 117
          local.get 114
          local.get 117
          i32.add
          local.set 118
          local.get 113
          local.get 118
          local.get 112
          call_indirect (type 0)
          local.set 119
          block  ;; label = @4
            local.get 119
            br_if 0 (;@4;)
            local.get 7
            i32.load offset=44
            local.set 120
            local.get 7
            i32.load offset=40
            local.set 121
            local.get 7
            i32.load offset=20
            local.set 122
            local.get 7
            i32.load offset=12
            local.set 123
            i32.const -1
            local.set 124
            local.get 123
            local.get 124
            i32.add
            local.set 125
            local.get 7
            local.get 125
            i32.store offset=12
            local.get 120
            local.get 121
            local.get 122
            local.get 125
            call $exch
          end
          br 1 (;@2;)
        end
      end
      local.get 7
      i32.load offset=44
      local.set 126
      local.get 7
      i32.load offset=40
      local.set 127
      local.get 7
      i32.load offset=24
      local.set 128
      local.get 7
      i32.load offset=32
      local.set 129
      local.get 126
      local.get 127
      local.get 128
      local.get 129
      call $exch
      local.get 7
      i32.load offset=24
      local.set 130
      i32.const 1
      local.set 131
      local.get 130
      local.get 131
      i32.sub
      local.set 132
      local.get 7
      local.get 132
      i32.store offset=20
      local.get 7
      i32.load offset=24
      local.set 133
      i32.const 1
      local.set 134
      local.get 133
      local.get 134
      i32.add
      local.set 135
      local.get 7
      local.get 135
      i32.store offset=24
      local.get 7
      i32.load offset=36
      local.set 136
      local.get 7
      local.get 136
      i32.store offset=8
      block  ;; label = @2
        loop  ;; label = @3
          local.get 7
          i32.load offset=8
          local.set 137
          local.get 7
          i32.load offset=16
          local.set 138
          local.get 137
          local.set 139
          local.get 138
          local.set 140
          local.get 139
          local.get 140
          i32.lt_s
          local.set 141
          i32.const 1
          local.set 142
          local.get 141
          local.get 142
          i32.and
          local.set 143
          local.get 143
          i32.eqz
          br_if 1 (;@2;)
          local.get 7
          i32.load offset=44
          local.set 144
          local.get 7
          i32.load offset=40
          local.set 145
          local.get 7
          i32.load offset=8
          local.set 146
          local.get 7
          i32.load offset=20
          local.set 147
          local.get 144
          local.get 145
          local.get 146
          local.get 147
          call $exch
          local.get 7
          i32.load offset=8
          local.set 148
          i32.const 1
          local.set 149
          local.get 148
          local.get 149
          i32.add
          local.set 150
          local.get 7
          local.get 150
          i32.store offset=8
          local.get 7
          i32.load offset=20
          local.set 151
          i32.const -1
          local.set 152
          local.get 151
          local.get 152
          i32.add
          local.set 153
          local.get 7
          local.get 153
          i32.store offset=20
          br 0 (;@3;)
        end
      end
      local.get 7
      i32.load offset=32
      local.set 154
      i32.const 1
      local.set 155
      local.get 154
      local.get 155
      i32.sub
      local.set 156
      local.get 7
      local.get 156
      i32.store offset=8
      block  ;; label = @2
        loop  ;; label = @3
          local.get 7
          i32.load offset=8
          local.set 157
          local.get 7
          i32.load offset=12
          local.set 158
          local.get 157
          local.set 159
          local.get 158
          local.set 160
          local.get 159
          local.get 160
          i32.gt_s
          local.set 161
          i32.const 1
          local.set 162
          local.get 161
          local.get 162
          i32.and
          local.set 163
          local.get 163
          i32.eqz
          br_if 1 (;@2;)
          local.get 7
          i32.load offset=44
          local.set 164
          local.get 7
          i32.load offset=40
          local.set 165
          local.get 7
          i32.load offset=24
          local.set 166
          local.get 7
          i32.load offset=8
          local.set 167
          local.get 164
          local.get 165
          local.get 166
          local.get 167
          call $exch
          local.get 7
          i32.load offset=8
          local.set 168
          i32.const -1
          local.set 169
          local.get 168
          local.get 169
          i32.add
          local.set 170
          local.get 7
          local.get 170
          i32.store offset=8
          local.get 7
          i32.load offset=24
          local.set 171
          i32.const 1
          local.set 172
          local.get 171
          local.get 172
          i32.add
          local.set 173
          local.get 7
          local.get 173
          i32.store offset=24
          br 0 (;@3;)
        end
      end
      local.get 7
      i32.load offset=44
      local.set 174
      local.get 7
      i32.load offset=40
      local.set 175
      local.get 7
      i32.load offset=36
      local.set 176
      local.get 7
      i32.load offset=20
      local.set 177
      local.get 7
      i32.load offset=28
      local.set 178
      local.get 174
      local.get 175
      local.get 176
      local.get 177
      local.get 178
      call $quicksort
      local.get 7
      i32.load offset=44
      local.set 179
      local.get 7
      i32.load offset=40
      local.set 180
      local.get 7
      i32.load offset=24
      local.set 181
      local.get 7
      i32.load offset=32
      local.set 182
      local.get 7
      i32.load offset=28
      local.set 183
      local.get 179
      local.get 180
      local.get 181
      local.get 182
      local.get 183
      call $quicksort
    end
    i32.const 48
    local.set 184
    local.get 7
    local.get 184
    i32.add
    local.set 185
    local.get 185
    global.set 0
    return)
  (func $exch (type 4) (param i32 i32 i32 i32)
    (local i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32)
    global.get 0
    local.set 4
    i32.const 32
    local.set 5
    local.get 4
    local.get 5
    i32.sub
    local.set 6
    local.get 6
    local.get 0
    i32.store offset=28
    local.get 6
    local.get 1
    i32.store offset=24
    local.get 6
    local.get 2
    i32.store offset=20
    local.get 6
    local.get 3
    i32.store offset=16
    local.get 6
    i32.load offset=28
    local.set 7
    local.get 6
    i32.load offset=20
    local.set 8
    local.get 6
    i32.load offset=24
    local.set 9
    local.get 8
    local.get 9
    i32.mul
    local.set 10
    local.get 7
    local.get 10
    i32.add
    local.set 11
    local.get 6
    local.get 11
    i32.store offset=12
    local.get 6
    i32.load offset=28
    local.set 12
    local.get 6
    i32.load offset=16
    local.set 13
    local.get 6
    i32.load offset=24
    local.set 14
    local.get 13
    local.get 14
    i32.mul
    local.set 15
    local.get 12
    local.get 15
    i32.add
    local.set 16
    local.get 6
    local.get 16
    i32.store offset=8
    block  ;; label = @1
      loop  ;; label = @2
        local.get 6
        i32.load offset=24
        local.set 17
        local.get 17
        i32.eqz
        br_if 1 (;@1;)
        local.get 6
        i32.load offset=12
        local.set 18
        local.get 18
        i32.load8_u
        local.set 19
        local.get 6
        local.get 19
        i32.store8 offset=7
        local.get 6
        i32.load offset=8
        local.set 20
        local.get 20
        i32.load8_u
        local.set 21
        local.get 6
        i32.load offset=12
        local.set 22
        local.get 22
        local.get 21
        i32.store8
        local.get 6
        i32.load8_u offset=7
        local.set 23
        local.get 6
        i32.load offset=8
        local.set 24
        local.get 24
        local.get 23
        i32.store8
        local.get 6
        i32.load offset=24
        local.set 25
        i32.const -1
        local.set 26
        local.get 25
        local.get 26
        i32.add
        local.set 27
        local.get 6
        local.get 27
        i32.store offset=24
        local.get 6
        i32.load offset=12
        local.set 28
        i32.const 1
        local.set 29
        local.get 28
        local.get 29
        i32.add
        local.set 30
        local.get 6
        local.get 30
        i32.store offset=12
        local.get 6
        i32.load offset=8
        local.set 31
        i32.const 1
        local.set 32
        local.get 31
        local.get 32
        i32.add
        local.set 33
        local.get 6
        local.get 33
        i32.store offset=8
        br 0 (;@2;)
      end
    end
    return)
  (func $__WASP_alloc (type 0) (param i32 i32) (result i32)
    (local i32 i32 i32 i32)
    global.get 0
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
  (func $__WASP_dealloc (type 3) (param i32)
    (local i32 i32 i32)
    global.get 0
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
    global.get 0
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
  (table (;0;) 2 2 funcref)
  (memory (;0;) 2)
  (global (;0;) (mut i32) (i32.const 66624))
  (export "memory" (memory 0))
  (export "__original_main" (func $__original_main))
  (elem (;0;) (i32.const 1) $intcmp)
  (data (;0;) (i32.const 1024) "v\00u\00e\00%d \00%d\0a\00")
  (data (;1;) (i32.const 1040) "@\04\01\00"))
