(module
  (type (;0;) (func (param i32) (result i32)))
  (type (;1;) (func (result i32)))
  (type (;2;) (func (param i32 i32 i32)))
  (type (;3;) (func))
  (type (;4;) (func (param i32 i32 i32 i32) (result i32)))
  (type (;5;) (func (param i32 i32)))
  (type (;6;) (func (param i32 i32 i32) (result i32)))
  (type (;7;) (func (param i32 i32) (result i32)))
  (type (;8;) (func (param i32)))
  (func $abs (type 0) (param i32) (result i32)
    (local i32)
    global.get $__stack_pointer
    i32.const 16
    i32.sub
    local.tee 1
    local.get 0
    i32.store offset=8
    block  ;; label = @1
      block  ;; label = @2
        local.get 1
        i32.load offset=8
        i32.const 0
        i32.lt_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 0 (;@2;)
        local.get 1
        i32.const 0
        local.get 1
        i32.load offset=8
        i32.sub
        i32.store offset=12
        br 1 (;@1;)
      end
      local.get 1
      local.get 1
      i32.load offset=8
      i32.store offset=12
    end
    local.get 1
    i32.load offset=12)
  (func $__original_main (type 1) (result i32)
    (local i32 i32)
    global.get $__stack_pointer
    i32.const 32
    i32.sub
    local.tee 0
    global.set $__stack_pointer
    i32.const 0
    i32.const 1035
    call $__WASP_symb_int
    i32.store offset=1068
    i32.const 0
    i32.const 1046
    call $__WASP_symb_int
    i32.store offset=1072
    i32.const 0
    i32.const 1024
    call $__WASP_symb_int
    i32.store offset=1076
    i32.const 0
    i32.const 0
    i32.load offset=1068
    i32.const 2
    i32.add
    i32.const 0
    i32.load offset=1072
    i32.const 1
    i32.shl
    i32.add
    i32.store offset=1080
    i32.const 0
    i32.const 0
    i32.load offset=1080
    i32.const 12
    call $calloc
    i32.store offset=1084
    i32.const 0
    i32.const 0
    i32.load offset=1080
    i32.const 4
    call $calloc
    i32.store offset=1088
    local.get 0
    i32.const 0
    i32.store offset=28
    block  ;; label = @1
      loop  ;; label = @2
        local.get 0
        i32.load offset=28
        i32.const 0
        i32.load offset=1080
        i32.lt_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        i32.const 1000
        i32.const 16
        call $calloc
        local.set 1
        i32.const 0
        i32.load offset=1084
        local.get 0
        i32.load offset=28
        i32.const 12
        i32.mul
        i32.add
        local.get 1
        i32.store offset=8
        i32.const 0
        i32.load offset=1084
        local.get 0
        i32.load offset=28
        i32.const 12
        i32.mul
        i32.add
        i32.const 1000
        i32.store
        i32.const 0
        i32.load offset=1084
        local.get 0
        i32.load offset=28
        i32.const 12
        i32.mul
        i32.add
        i32.const 0
        i32.store offset=4
        local.get 0
        local.get 0
        i32.load offset=28
        i32.const 1
        i32.add
        i32.store offset=28
        br 0 (;@2;)
      end
    end
    i32.const 0
    i32.const 2
    i32.store offset=1092
    i32.const 0
    i32.const 0
    i32.load offset=1092
    i32.const 0
    i32.load offset=1068
    i32.add
    local.tee 1
    i32.store offset=1096
    i32.const 0
    local.get 1
    i32.store offset=1100
    i32.const 0
    i32.const 0
    i32.load offset=1096
    i32.const 0
    i32.load offset=1072
    i32.const 1
    i32.shl
    i32.add
    i32.store offset=1104
    local.get 0
    i32.const 0
    i32.load offset=1092
    i32.store offset=28
    block  ;; label = @1
      loop  ;; label = @2
        local.get 0
        i32.load offset=28
        i32.const 0
        i32.load offset=1100
        i32.lt_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        local.get 0
        i32.const 0
        i32.store offset=24
        local.get 0
        i32.const 1026
        call $__WASP_symb_int
        i32.store offset=24
        local.get 0
        i32.load offset=28
        i32.const 0
        local.get 0
        i32.load offset=24
        call $addArc
        local.get 0
        local.get 0
        i32.load offset=28
        i32.const 1
        i32.add
        i32.store offset=28
        br 0 (;@2;)
      end
    end
    local.get 0
    i32.const 0
    i32.load offset=1096
    i32.store offset=28
    block  ;; label = @1
      loop  ;; label = @2
        local.get 0
        i32.load offset=28
        i32.const 0
        i32.load offset=1096
        i32.const 0
        i32.load offset=1072
        i32.add
        i32.lt_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        local.get 0
        i32.const 0
        i32.store offset=20
        local.get 0
        i32.const 1037
        call $__WASP_symb_int
        i32.store offset=20
        local.get 0
        i32.load offset=28
        i32.const 0
        i32.load offset=1072
        i32.add
        local.get 0
        i32.load offset=28
        local.get 0
        i32.load offset=20
        call $addArc
        local.get 0
        local.get 0
        i32.load offset=28
        i32.const 1
        i32.add
        i32.store offset=28
        br 0 (;@2;)
      end
    end
    local.get 0
    i32.const 0
    i32.store offset=28
    block  ;; label = @1
      loop  ;; label = @2
        local.get 0
        i32.load offset=28
        i32.const 0
        i32.load offset=1076
        i32.lt_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        local.get 0
        i32.const 1033
        call $__WASP_symb_int
        i32.store offset=16
        local.get 0
        i32.const 1049
        call $__WASP_symb_int
        i32.store offset=12
        local.get 0
        i32.const 1051
        call $__WASP_symb_int
        i32.store offset=8
        block  ;; label = @3
          local.get 0
          i32.load offset=16
          i32.const 0
          i32.load offset=1096
          i32.ge_s
          i32.const 1
          i32.and
          i32.eqz
          br_if 0 (;@3;)
          local.get 0
          i32.load offset=16
          i32.const 0
          i32.load offset=1096
          i32.const 0
          i32.load offset=1072
          i32.add
          i32.lt_s
          i32.const 1
          i32.and
          i32.eqz
          br_if 0 (;@3;)
          local.get 0
          local.get 0
          i32.load offset=16
          i32.const 0
          i32.load offset=1072
          i32.add
          i32.store offset=16
        end
        local.get 0
        i32.load offset=12
        local.get 0
        i32.load offset=16
        local.get 0
        i32.load offset=8
        call $addArc
        local.get 0
        local.get 0
        i32.load offset=28
        i32.const 1
        i32.add
        i32.store offset=28
        br 0 (;@2;)
      end
    end
    call $FordFulkersonAndCut
    local.get 0
    i32.const 0
    i32.store offset=28
    block  ;; label = @1
      loop  ;; label = @2
        local.get 0
        i32.load offset=28
        i32.const 0
        i32.load offset=1080
        i32.lt_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        i32.const 0
        i32.load offset=1084
        local.get 0
        i32.load offset=28
        i32.const 12
        i32.mul
        i32.add
        i32.load offset=8
        call $free
        local.get 0
        local.get 0
        i32.load offset=28
        i32.const 1
        i32.add
        i32.store offset=28
        br 0 (;@2;)
      end
    end
    i32.const 0
    i32.load offset=1084
    call $free
    local.get 0
    i32.const 32
    i32.add
    global.set $__stack_pointer
    i32.const 0)
  (func $addArc (type 2) (param i32 i32 i32)
    (local i32)
    global.get $__stack_pointer
    i32.const 16
    i32.sub
    local.tee 3
    global.set $__stack_pointer
    local.get 3
    local.get 0
    i32.store offset=12
    local.get 3
    local.get 1
    i32.store offset=8
    local.get 3
    local.get 2
    i32.store offset=4
    local.get 3
    local.get 3
    i32.load offset=12
    local.get 3
    i32.load offset=8
    local.get 3
    i32.load offset=4
    i32.const 0
    call $addArcSingle
    i32.store
    local.get 3
    i32.load offset=8
    local.get 3
    i32.load offset=12
    i32.const 0
    local.get 3
    i32.load offset=4
    i32.sub
    local.get 3
    i32.load
    call $addArcSingle
    drop
    local.get 3
    i32.const 16
    i32.add
    global.set $__stack_pointer)
  (func $FordFulkersonAndCut (type 3)
    (local i32 i32 i32 i32)
    global.get $__stack_pointer
    i32.const 112
    i32.sub
    local.tee 0
    global.set $__stack_pointer
    local.get 0
    i32.const 1000
    i32.store offset=56
    local.get 0
    i32.const 0
    i32.store offset=60
    local.get 0
    local.get 0
    i32.load offset=56
    i32.const 4
    call $calloc
    i32.store offset=64
    local.get 0
    local.get 0
    i32.const 56
    i32.add
    call $FordFulkerson
    i32.store offset=96
    local.get 0
    local.get 0
    i32.load offset=96
    i32.store offset=92
    i32.const 0
    i32.const 1
    i32.store8 offset=1108
    local.get 0
    i32.const 56
    i32.add
    local.get 0
    i32.const 92
    i32.add
    call $dfs
    drop
    local.get 0
    i32.const 0
    i32.load offset=1080
    i32.const 4
    call $calloc
    i32.store offset=88
    local.get 0
    i32.const 0
    i32.store offset=108
    block  ;; label = @1
      loop  ;; label = @2
        local.get 0
        i32.load offset=108
        i32.const 0
        i32.load offset=1080
        i32.lt_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        local.get 0
        i32.load offset=88
        local.get 0
        i32.load offset=108
        i32.const 2
        i32.shl
        i32.add
        i32.const 0
        i32.store
        local.get 0
        local.get 0
        i32.load offset=108
        i32.const 1
        i32.add
        i32.store offset=108
        br 0 (;@2;)
      end
    end
    local.get 0
    i32.load offset=88
    i32.const 1
    i32.store offset=4
    local.get 0
    i32.const 0
    i32.store offset=108
    block  ;; label = @1
      loop  ;; label = @2
        local.get 0
        i32.load offset=108
        local.get 0
        i32.load offset=60
        i32.lt_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        local.get 0
        local.get 0
        i32.load offset=64
        local.get 0
        i32.load offset=108
        i32.const 2
        i32.shl
        i32.add
        i32.load
        i32.store offset=52
        local.get 0
        i32.load offset=88
        local.get 0
        i32.load offset=52
        i32.load
        i32.const 2
        i32.shl
        i32.add
        i32.const 1
        i32.store
        local.get 0
        local.get 0
        i32.load offset=108
        i32.const 1
        i32.add
        i32.store offset=108
        br 0 (;@2;)
      end
    end
    local.get 0
    local.get 0
    i32.load offset=96
    i32.store offset=32
    i32.const 1058
    local.get 0
    i32.const 32
    i32.add
    call $printf
    drop
    local.get 0
    i32.const 0
    i32.store8 offset=71
    local.get 0
    i32.const 0
    i32.load offset=1096
    i32.store offset=108
    block  ;; label = @1
      loop  ;; label = @2
        local.get 0
        i32.load offset=108
        i32.const 0
        i32.load offset=1096
        i32.const 0
        i32.load offset=1072
        i32.add
        i32.lt_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        block  ;; label = @3
          block  ;; label = @4
            block  ;; label = @5
              local.get 0
              i32.load offset=88
              local.get 0
              i32.load offset=108
              i32.const 2
              i32.shl
              i32.add
              i32.load
              i32.eqz
              br_if 0 (;@5;)
              local.get 0
              i32.load offset=88
              local.get 0
              i32.load offset=108
              i32.const 0
              i32.load offset=1072
              i32.add
              i32.const 2
              i32.shl
              i32.add
              i32.load
              i32.eqz
              br_if 1 (;@4;)
            end
            local.get 0
            i32.load offset=88
            local.get 0
            i32.load offset=108
            i32.const 2
            i32.shl
            i32.add
            i32.load
            br_if 1 (;@3;)
            local.get 0
            i32.load offset=88
            local.get 0
            i32.load offset=108
            i32.const 0
            i32.load offset=1072
            i32.add
            i32.const 2
            i32.shl
            i32.add
            i32.load
            i32.eqz
            br_if 1 (;@3;)
          end
          block  ;; label = @4
            local.get 0
            i32.load8_u offset=71
            i32.const 255
            i32.and
            i32.const 0
            i32.const 255
            i32.and
            i32.ne
            i32.const 1
            i32.and
            i32.eqz
            br_if 0 (;@4;)
            i32.const 1053
            i32.const 0
            call $printf
            drop
          end
          local.get 0
          local.get 0
          i32.load offset=108
          i32.store
          i32.const 1048
          local.get 0
          call $printf
          drop
          local.get 0
          i32.const 1
          i32.store8 offset=71
        end
        local.get 0
        local.get 0
        i32.load offset=108
        i32.const 1
        i32.add
        i32.store offset=108
        br 0 (;@2;)
      end
    end
    i32.const 1060
    i32.const 0
    call $printf
    drop
    local.get 0
    i32.const 1
    i32.store offset=108
    block  ;; label = @1
      loop  ;; label = @2
        local.get 0
        i32.load offset=108
        i32.const 0
        i32.load offset=1104
        i32.lt_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        block  ;; label = @3
          block  ;; label = @4
            local.get 0
            i32.load offset=88
            local.get 0
            i32.load offset=108
            i32.const 2
            i32.shl
            i32.add
            i32.load
            i32.eqz
            br_if 0 (;@4;)
            br 1 (;@3;)
          end
          local.get 0
          i32.const 0
          i32.load offset=1084
          local.get 0
          i32.load offset=108
          i32.const 12
          i32.mul
          i32.add
          i32.load offset=4
          i32.const 4
          call $calloc
          i32.store offset=84
          local.get 0
          i32.const 0
          i32.store offset=80
          local.get 0
          i32.const 0
          i32.store offset=104
          block  ;; label = @4
            loop  ;; label = @5
              local.get 0
              i32.load offset=104
              i32.const 0
              i32.load offset=1084
              local.get 0
              i32.load offset=108
              i32.const 12
              i32.mul
              i32.add
              i32.load offset=4
              i32.lt_s
              i32.const 1
              i32.and
              i32.eqz
              br_if 1 (;@4;)
              local.get 0
              i32.const 0
              i32.load offset=1084
              local.get 0
              i32.load offset=108
              i32.const 12
              i32.mul
              i32.add
              i32.load offset=8
              local.get 0
              i32.load offset=104
              i32.const 4
              i32.shl
              i32.add
              i32.store offset=48
              local.get 0
              local.get 0
              i32.load offset=48
              i32.load
              i32.store offset=76
              block  ;; label = @6
                block  ;; label = @7
                  local.get 0
                  i32.load offset=88
                  local.get 0
                  i32.load offset=76
                  i32.const 2
                  i32.shl
                  i32.add
                  i32.load
                  br_if 0 (;@7;)
                  br 1 (;@6;)
                end
                block  ;; label = @7
                  local.get 0
                  i32.load offset=76
                  br_if 0 (;@7;)
                  br 1 (;@6;)
                end
                block  ;; label = @7
                  local.get 0
                  i32.load offset=48
                  i32.load offset=4
                  i32.const 0
                  i32.gt_s
                  i32.const 1
                  i32.and
                  i32.eqz
                  br_if 0 (;@7;)
                  br 1 (;@6;)
                end
                block  ;; label = @7
                  local.get 0
                  i32.load offset=48
                  i32.load offset=4
                  local.get 0
                  i32.load offset=48
                  i32.load offset=8
                  i32.ne
                  i32.const 1
                  i32.and
                  i32.eqz
                  br_if 0 (;@7;)
                  br 1 (;@6;)
                end
                block  ;; label = @7
                  local.get 0
                  i32.load offset=76
                  i32.const 0
                  i32.load offset=1096
                  i32.const 0
                  i32.load offset=1072
                  i32.add
                  i32.ge_s
                  i32.const 1
                  i32.and
                  i32.eqz
                  br_if 0 (;@7;)
                  local.get 0
                  i32.load offset=76
                  i32.const 0
                  i32.load offset=1104
                  i32.lt_s
                  i32.const 1
                  i32.and
                  i32.eqz
                  br_if 0 (;@7;)
                  local.get 0
                  i32.load offset=108
                  i32.const 0
                  i32.load offset=1096
                  i32.ge_s
                  i32.const 1
                  i32.and
                  i32.eqz
                  br_if 0 (;@7;)
                  local.get 0
                  i32.load offset=108
                  i32.const 0
                  i32.load offset=1096
                  i32.const 0
                  i32.load offset=1072
                  i32.add
                  i32.lt_s
                  i32.const 1
                  i32.and
                  i32.eqz
                  br_if 0 (;@7;)
                  br 1 (;@6;)
                end
                block  ;; label = @7
                  local.get 0
                  i32.load offset=76
                  i32.const 0
                  i32.load offset=1096
                  i32.const 0
                  i32.load offset=1072
                  i32.add
                  i32.ge_s
                  i32.const 1
                  i32.and
                  i32.eqz
                  br_if 0 (;@7;)
                  local.get 0
                  i32.load offset=76
                  i32.const 0
                  i32.load offset=1104
                  i32.lt_s
                  i32.const 1
                  i32.and
                  i32.eqz
                  br_if 0 (;@7;)
                  local.get 0
                  local.get 0
                  i32.load offset=76
                  i32.const 0
                  i32.load offset=1072
                  i32.sub
                  i32.store offset=76
                end
                local.get 0
                i32.load offset=76
                local.set 1
                local.get 0
                i32.load offset=84
                local.set 2
                local.get 0
                local.get 0
                i32.load offset=80
                local.tee 3
                i32.const 1
                i32.add
                i32.store offset=80
                local.get 2
                local.get 3
                i32.const 2
                i32.shl
                i32.add
                local.get 1
                i32.store
              end
              local.get 0
              local.get 0
              i32.load offset=104
              i32.const 1
              i32.add
              i32.store offset=104
              br 0 (;@5;)
            end
          end
          local.get 0
          i32.load offset=84
          local.get 0
          i32.load offset=80
          call $Sort_Quick_Vector
          local.get 0
          local.get 0
          i32.load offset=108
          i32.store offset=72
          block  ;; label = @4
            local.get 0
            i32.load offset=72
            i32.const 0
            i32.load offset=1096
            i32.const 0
            i32.load offset=1072
            i32.add
            i32.ge_s
            i32.const 1
            i32.and
            i32.eqz
            br_if 0 (;@4;)
            local.get 0
            i32.load offset=72
            i32.const 0
            i32.load offset=1104
            i32.lt_s
            i32.const 1
            i32.and
            i32.eqz
            br_if 0 (;@4;)
            local.get 0
            local.get 0
            i32.load offset=72
            i32.const 0
            i32.load offset=1072
            i32.sub
            i32.store offset=72
          end
          local.get 0
          i32.const 0
          i32.store offset=100
          block  ;; label = @4
            loop  ;; label = @5
              local.get 0
              i32.load offset=100
              local.get 0
              i32.load offset=80
              i32.lt_s
              i32.const 1
              i32.and
              i32.eqz
              br_if 1 (;@4;)
              local.get 0
              i32.load offset=72
              local.set 1
              local.get 0
              local.get 0
              i32.load offset=84
              local.get 0
              i32.load offset=100
              i32.const 2
              i32.shl
              i32.add
              i32.load
              i32.store offset=20
              local.get 0
              local.get 1
              i32.store offset=16
              i32.const 1055
              local.get 0
              i32.const 16
              i32.add
              call $printf
              drop
              local.get 0
              local.get 0
              i32.load offset=100
              i32.const 1
              i32.add
              i32.store offset=100
              br 0 (;@5;)
            end
          end
          local.get 0
          i32.load offset=84
          call $free
        end
        local.get 0
        local.get 0
        i32.load offset=108
        i32.const 1
        i32.add
        i32.store offset=108
        br 0 (;@2;)
      end
    end
    local.get 0
    i32.load offset=64
    call $free
    local.get 0
    i32.load offset=88
    call $free
    local.get 0
    i32.const 112
    i32.add
    global.set $__stack_pointer)
  (func $addArcSingle (type 4) (param i32 i32 i32 i32) (result i32)
    (local i32)
    global.get $__stack_pointer
    i32.const 32
    i32.sub
    local.tee 4
    global.set $__stack_pointer
    local.get 4
    local.get 0
    i32.store offset=28
    local.get 4
    local.get 1
    i32.store offset=24
    local.get 4
    local.get 2
    i32.store offset=20
    local.get 4
    local.get 3
    i32.store offset=16
    i32.const 0
    i32.load offset=1084
    local.get 4
    i32.load offset=28
    i32.const 12
    i32.mul
    i32.add
    i32.const 0
    i32.load offset=1084
    local.get 4
    i32.load offset=28
    i32.const 12
    i32.mul
    i32.add
    i32.load offset=4
    i32.const 1
    i32.add
    i32.store offset=4
    local.get 4
    i32.const 0
    i32.load offset=1084
    local.get 4
    i32.load offset=28
    i32.const 12
    i32.mul
    i32.add
    i32.load
    i32.store offset=12
    block  ;; label = @1
      i32.const 0
      i32.load offset=1084
      local.get 4
      i32.load offset=28
      i32.const 12
      i32.mul
      i32.add
      i32.load offset=4
      local.get 4
      i32.load offset=12
      i32.gt_s
      i32.const 1
      i32.and
      i32.eqz
      br_if 0 (;@1;)
      i32.const 0
      i32.load offset=1084
      local.get 4
      i32.load offset=28
      i32.const 12
      i32.mul
      i32.add
      local.get 4
      i32.load offset=12
      i32.const 1
      i32.shl
      i32.store
      i32.const 0
      i32.load offset=1084
      local.get 4
      i32.load offset=28
      i32.const 12
      i32.mul
      i32.add
      i32.load offset=8
      i32.const 0
      i32.load offset=1084
      local.get 4
      i32.load offset=28
      i32.const 12
      i32.mul
      i32.add
      i32.load
      i32.const 4
      i32.shl
      call $realloc
      local.set 0
      i32.const 0
      i32.load offset=1084
      local.get 4
      i32.load offset=28
      i32.const 12
      i32.mul
      i32.add
      local.get 0
      i32.store offset=8
    end
    local.get 4
    i32.const 0
    i32.load offset=1084
    local.get 4
    i32.load offset=28
    i32.const 12
    i32.mul
    i32.add
    i32.load offset=8
    i32.const 0
    i32.load offset=1084
    local.get 4
    i32.load offset=28
    i32.const 12
    i32.mul
    i32.add
    i32.load offset=4
    i32.const 1
    i32.sub
    i32.const 4
    i32.shl
    i32.add
    i32.store offset=8
    local.get 4
    i32.load offset=8
    local.get 4
    i32.load offset=24
    i32.store
    local.get 4
    i32.load offset=8
    local.get 4
    i32.load offset=20
    i32.store offset=4
    local.get 4
    i32.load offset=8
    i32.const 0
    i32.store offset=8
    block  ;; label = @1
      block  ;; label = @2
        local.get 4
        i32.load offset=16
        i32.const 0
        i32.eq
        i32.const 1
        i32.and
        i32.eqz
        br_if 0 (;@2;)
        local.get 4
        i32.load offset=8
        i32.const 0
        i32.store offset=12
        br 1 (;@1;)
      end
      local.get 4
      i32.load offset=8
      local.get 4
      i32.load offset=16
      i32.store offset=12
      local.get 4
      i32.load offset=16
      local.get 4
      i32.load offset=8
      i32.store offset=12
    end
    local.get 4
    i32.load offset=8
    local.set 0
    local.get 4
    i32.const 32
    i32.add
    global.set $__stack_pointer
    local.get 0)
  (func $pArcList_add (type 5) (param i32 i32)
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
    i32.load offset=12
    local.get 2
    i32.load offset=12
    i32.load offset=4
    i32.const 1
    i32.add
    i32.store offset=4
    local.get 2
    local.get 2
    i32.load offset=12
    i32.load
    i32.store offset=4
    block  ;; label = @1
      local.get 2
      i32.load offset=12
      i32.load offset=4
      local.get 2
      i32.load offset=4
      i32.gt_s
      i32.const 1
      i32.and
      i32.eqz
      br_if 0 (;@1;)
      local.get 2
      i32.load offset=12
      local.get 2
      i32.load offset=4
      i32.const 1
      i32.shl
      i32.store
      local.get 2
      i32.load offset=12
      i32.load offset=8
      local.get 2
      i32.load offset=12
      i32.load
      i32.const 2
      i32.shl
      call $realloc
      local.set 0
      local.get 2
      i32.load offset=12
      local.get 0
      i32.store offset=8
    end
    local.get 2
    i32.load offset=12
    i32.load offset=8
    local.get 2
    i32.load offset=12
    i32.load offset=4
    i32.const 1
    i32.sub
    i32.const 2
    i32.shl
    i32.add
    local.get 2
    i32.load offset=8
    i32.store
    local.get 2
    i32.const 16
    i32.add
    global.set $__stack_pointer)
  (func $addFlowSingle (type 5) (param i32 i32)
    (local i32)
    global.get $__stack_pointer
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
    local.tee 0
    local.get 0
    i32.load offset=8
    local.get 2
    i32.load offset=8
    i32.add
    i32.store offset=8)
  (func $addFlow (type 5) (param i32 i32)
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
    i32.load offset=12
    local.get 2
    i32.load offset=8
    call $addFlowSingle
    block  ;; label = @1
      local.get 2
      i32.load offset=12
      i32.load offset=12
      i32.const 0
      i32.ne
      i32.const 1
      i32.and
      i32.eqz
      br_if 0 (;@1;)
      local.get 2
      i32.load offset=12
      i32.load offset=12
      i32.const 0
      local.get 2
      i32.load offset=8
      i32.sub
      call $addFlowSingle
    end
    local.get 2
    i32.const 16
    i32.add
    global.set $__stack_pointer)
  (func $dfs_visit (type 6) (param i32 i32 i32) (result i32)
    (local i32)
    global.get $__stack_pointer
    i32.const 32
    i32.sub
    local.tee 3
    global.set $__stack_pointer
    local.get 3
    local.get 0
    i32.store offset=24
    local.get 3
    local.get 1
    i32.store offset=20
    local.get 3
    local.get 2
    i32.store offset=16
    block  ;; label = @1
      block  ;; label = @2
        local.get 3
        i32.load offset=24
        br_if 0 (;@2;)
        local.get 3
        i32.const 1
        i32.store8 offset=31
        br 1 (;@1;)
      end
      i32.const 0
      i32.load offset=1088
      local.get 3
      i32.load offset=24
      i32.const 2
      i32.shl
      i32.add
      i32.const 1
      i32.store
      local.get 3
      i32.const 0
      i32.store offset=12
      block  ;; label = @2
        loop  ;; label = @3
          local.get 3
          i32.load offset=12
          i32.const 0
          i32.load offset=1084
          local.get 3
          i32.load offset=24
          i32.const 12
          i32.mul
          i32.add
          i32.load offset=4
          i32.lt_s
          i32.const 1
          i32.and
          i32.eqz
          br_if 1 (;@2;)
          local.get 3
          i32.const 0
          i32.load offset=1084
          local.get 3
          i32.load offset=24
          i32.const 12
          i32.mul
          i32.add
          i32.load offset=8
          local.get 3
          i32.load offset=12
          i32.const 4
          i32.shl
          i32.add
          i32.store
          block  ;; label = @4
            block  ;; label = @5
              block  ;; label = @6
                local.get 3
                i32.load
                i32.load offset=4
                i32.const 0
                i32.lt_s
                i32.const 1
                i32.and
                i32.eqz
                br_if 0 (;@6;)
                block  ;; label = @7
                  local.get 3
                  i32.load
                  i32.load offset=8
                  br_if 0 (;@7;)
                  br 3 (;@4;)
                end
                local.get 3
                local.get 3
                i32.load
                i32.load offset=8
                call $abs
                i32.store offset=4
                br 1 (;@5;)
              end
              local.get 3
              local.get 3
              i32.load
              i32.load offset=4
              local.get 3
              i32.load
              i32.load offset=8
              i32.sub
              call $abs
              i32.store offset=4
              block  ;; label = @6
                local.get 3
                i32.load offset=4
                br_if 0 (;@6;)
                br 2 (;@4;)
              end
            end
            local.get 3
            i32.const 0
            i32.load offset=1084
            local.get 3
            i32.load offset=24
            i32.const 12
            i32.mul
            i32.add
            i32.load offset=8
            local.get 3
            i32.load offset=12
            i32.const 4
            i32.shl
            i32.add
            i32.load
            i32.store offset=8
            block  ;; label = @5
              i32.const 0
              i32.load8_u offset=1108
              i32.const 255
              i32.and
              i32.const 0
              i32.const 255
              i32.and
              i32.ne
              i32.const 1
              i32.and
              i32.eqz
              br_if 0 (;@5;)
              local.get 3
              i32.load offset=20
              local.get 3
              i32.load
              call $pArcList_add
            end
            block  ;; label = @5
              i32.const 0
              i32.load offset=1088
              local.get 3
              i32.load offset=8
              i32.const 2
              i32.shl
              i32.add
              i32.load
              br_if 0 (;@5;)
              block  ;; label = @6
                local.get 3
                i32.load offset=8
                local.get 3
                i32.load offset=20
                local.get 3
                i32.load offset=16
                call $dfs_visit
                i32.const 255
                i32.and
                i32.const 0
                i32.const 255
                i32.and
                i32.ne
                i32.const 1
                i32.and
                i32.eqz
                br_if 0 (;@6;)
                block  ;; label = @7
                  local.get 3
                  i32.load offset=16
                  i32.load
                  local.get 3
                  i32.load offset=4
                  i32.gt_s
                  i32.const 1
                  i32.and
                  i32.eqz
                  br_if 0 (;@7;)
                  local.get 3
                  i32.load offset=16
                  local.get 3
                  i32.load offset=4
                  i32.store
                end
                block  ;; label = @7
                  i32.const 0
                  i32.load8_u offset=1108
                  i32.const 255
                  i32.and
                  i32.const 0
                  i32.const 255
                  i32.and
                  i32.ne
                  i32.const 1
                  i32.and
                  br_if 0 (;@7;)
                  local.get 3
                  i32.load offset=20
                  local.get 3
                  i32.load
                  call $pArcList_add
                end
                local.get 3
                i32.const 1
                i32.store8 offset=31
                br 5 (;@1;)
              end
            end
          end
          local.get 3
          local.get 3
          i32.load offset=12
          i32.const 1
          i32.add
          i32.store offset=12
          br 0 (;@3;)
        end
      end
      local.get 3
      i32.const 0
      i32.store8 offset=31
    end
    local.get 3
    i32.load8_u offset=31
    local.set 0
    local.get 3
    i32.const 32
    i32.add
    global.set $__stack_pointer
    local.get 0
    i32.const 24
    i32.shl
    i32.const 24
    i32.shr_s)
  (func $dfs (type 7) (param i32 i32) (result i32)
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
    i32.load offset=8
    i32.const 2147483647
    i32.store
    local.get 2
    i32.load offset=12
    i32.const 0
    i32.store offset=4
    local.get 2
    i32.const 0
    i32.store offset=4
    block  ;; label = @1
      loop  ;; label = @2
        local.get 2
        i32.load offset=4
        i32.const 0
        i32.load offset=1080
        i32.lt_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        i32.const 0
        i32.load offset=1088
        local.get 2
        i32.load offset=4
        i32.const 2
        i32.shl
        i32.add
        i32.const 0
        i32.store
        local.get 2
        local.get 2
        i32.load offset=4
        i32.const 1
        i32.add
        i32.store offset=4
        br 0 (;@2;)
      end
    end
    i32.const 1
    local.get 2
    i32.load offset=12
    local.get 2
    i32.load offset=8
    call $dfs_visit
    local.set 0
    local.get 2
    i32.const 16
    i32.add
    global.set $__stack_pointer
    local.get 0
    i32.const 24
    i32.shl
    i32.const 24
    i32.shr_s)
  (func $FordFulkerson (type 0) (param i32) (result i32)
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
    i32.const 0
    i32.store offset=4
    local.get 1
    i32.const 0
    i32.store
    block  ;; label = @1
      loop  ;; label = @2
        local.get 1
        i32.load offset=12
        local.get 1
        i32.const 4
        i32.add
        call $dfs
        i32.const 255
        i32.and
        i32.const 0
        i32.const 255
        i32.and
        i32.ne
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        local.get 1
        i32.const 0
        i32.store offset=8
        block  ;; label = @3
          loop  ;; label = @4
            local.get 1
            i32.load offset=8
            local.get 1
            i32.load offset=12
            i32.load offset=4
            i32.lt_s
            i32.const 1
            i32.and
            i32.eqz
            br_if 1 (;@3;)
            local.get 1
            i32.load offset=12
            i32.load offset=8
            local.get 1
            i32.load offset=8
            i32.const 2
            i32.shl
            i32.add
            i32.load
            local.get 1
            i32.load offset=4
            call $addFlow
            local.get 1
            local.get 1
            i32.load offset=8
            i32.const 1
            i32.add
            i32.store offset=8
            br 0 (;@4;)
          end
        end
        local.get 1
        local.get 1
        i32.load
        local.get 1
        i32.load offset=4
        i32.add
        i32.store
        br 0 (;@2;)
      end
    end
    local.get 1
    i32.load
    local.set 0
    local.get 1
    i32.const 16
    i32.add
    global.set $__stack_pointer
    local.get 0)
  (func $Sort_Quick_Vector (type 5) (param i32 i32)
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
    block  ;; label = @1
      block  ;; label = @2
        local.get 2
        i32.load offset=8
        i32.const 0
        i32.le_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 0 (;@2;)
        br 1 (;@1;)
      end
      local.get 2
      i32.load offset=12
      i32.const 0
      local.get 2
      i32.load offset=8
      i32.const 1
      i32.sub
      call $Sort_Quick_Vector_Range
    end
    local.get 2
    i32.const 16
    i32.add
    global.set $__stack_pointer)
  (func $Sort_Quick_Vector_Range (type 2) (param i32 i32 i32)
    (local i32)
    global.get $__stack_pointer
    i32.const 16
    i32.sub
    local.tee 3
    global.set $__stack_pointer
    local.get 3
    local.get 0
    i32.store offset=12
    local.get 3
    local.get 1
    i32.store offset=8
    local.get 3
    local.get 2
    i32.store offset=4
    block  ;; label = @1
      block  ;; label = @2
        local.get 3
        i32.load offset=8
        local.get 3
        i32.load offset=4
        i32.gt_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 0 (;@2;)
        br 1 (;@1;)
      end
      block  ;; label = @2
        local.get 3
        i32.load offset=4
        local.get 3
        i32.load offset=8
        i32.le_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 0 (;@2;)
        br 1 (;@1;)
      end
      local.get 3
      local.get 3
      i32.load offset=12
      local.get 3
      i32.load offset=8
      local.get 3
      i32.load offset=4
      call $Quick_Partition
      i32.store
      local.get 3
      i32.load offset=12
      local.get 3
      i32.load offset=8
      local.get 3
      i32.load
      i32.const 1
      i32.sub
      call $Sort_Quick_Vector_Range
      local.get 3
      i32.load offset=12
      local.get 3
      i32.load
      i32.const 1
      i32.add
      local.get 3
      i32.load offset=4
      call $Sort_Quick_Vector_Range
    end
    local.get 3
    i32.const 16
    i32.add
    global.set $__stack_pointer)
  (func $Quick_Partition (type 6) (param i32 i32 i32) (result i32)
    (local i32)
    global.get $__stack_pointer
    i32.const 32
    i32.sub
    local.tee 3
    local.get 0
    i32.store offset=28
    local.get 3
    local.get 1
    i32.store offset=24
    local.get 3
    local.get 2
    i32.store offset=20
    local.get 3
    local.get 3
    i32.load offset=24
    i32.const 1
    i32.sub
    i32.store offset=16
    local.get 3
    local.get 3
    i32.load offset=20
    i32.store offset=8
    local.get 3
    local.get 3
    i32.load offset=28
    local.get 3
    i32.load offset=20
    i32.const 2
    i32.shl
    i32.add
    i32.load
    i32.store offset=4
    block  ;; label = @1
      loop  ;; label = @2
        local.get 3
        i32.load offset=16
        local.get 3
        i32.load offset=8
        i32.lt_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        block  ;; label = @3
          loop  ;; label = @4
            local.get 3
            i32.load offset=28
            local.set 0
            local.get 3
            local.get 3
            i32.load offset=16
            i32.const 1
            i32.add
            local.tee 1
            i32.store offset=16
            local.get 0
            local.get 1
            i32.const 2
            i32.shl
            i32.add
            i32.load
            local.get 3
            i32.load offset=4
            i32.lt_s
            i32.const 1
            i32.and
            i32.eqz
            br_if 1 (;@3;)
            br 0 (;@4;)
          end
        end
        block  ;; label = @3
          block  ;; label = @4
            loop  ;; label = @5
              local.get 3
              i32.load offset=4
              local.set 0
              local.get 3
              i32.load offset=28
              local.set 1
              local.get 3
              local.get 3
              i32.load offset=8
              i32.const -1
              i32.add
              local.tee 2
              i32.store offset=8
              local.get 0
              local.get 1
              local.get 2
              i32.const 2
              i32.shl
              i32.add
              i32.load
              i32.lt_s
              i32.const 1
              i32.and
              i32.eqz
              br_if 1 (;@4;)
              block  ;; label = @6
                local.get 3
                i32.load offset=8
                local.get 3
                i32.load offset=24
                i32.eq
                i32.const 1
                i32.and
                i32.eqz
                br_if 0 (;@6;)
                br 3 (;@3;)
              end
              br 0 (;@5;)
            end
          end
        end
        block  ;; label = @3
          local.get 3
          i32.load offset=16
          local.get 3
          i32.load offset=8
          i32.lt_s
          i32.const 1
          i32.and
          i32.eqz
          br_if 0 (;@3;)
          local.get 3
          local.get 3
          i32.load offset=28
          local.get 3
          i32.load offset=16
          i32.const 2
          i32.shl
          i32.add
          i32.load
          i32.store offset=12
          local.get 3
          i32.load offset=28
          local.get 3
          i32.load offset=16
          i32.const 2
          i32.shl
          i32.add
          local.get 3
          i32.load offset=28
          local.get 3
          i32.load offset=8
          i32.const 2
          i32.shl
          i32.add
          i32.load
          i32.store
          local.get 3
          i32.load offset=28
          local.get 3
          i32.load offset=8
          i32.const 2
          i32.shl
          i32.add
          local.get 3
          i32.load offset=12
          i32.store
        end
        br 0 (;@2;)
      end
    end
    local.get 3
    local.get 3
    i32.load offset=28
    local.get 3
    i32.load offset=16
    i32.const 2
    i32.shl
    i32.add
    i32.load
    i32.store offset=12
    local.get 3
    i32.load offset=28
    local.get 3
    i32.load offset=16
    i32.const 2
    i32.shl
    i32.add
    local.get 3
    i32.load offset=28
    local.get 3
    i32.load offset=20
    i32.const 2
    i32.shl
    i32.add
    i32.load
    i32.store
    local.get 3
    i32.load offset=28
    local.get 3
    i32.load offset=20
    i32.const 2
    i32.shl
    i32.add
    local.get 3
    i32.load offset=12
    i32.store
    local.get 3
    i32.load offset=16)
  (func $printf (type 7) (param i32 i32) (result i32)
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
  (func $calloc (type 7) (param i32 i32) (result i32)
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
    i32.load offset=1064
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
    i32.load offset=1064
    local.set 11
    local.get 11
    local.get 9
    i32.add
    local.set 12
    i32.const 0
    local.set 13
    local.get 13
    local.get 12
    i32.store offset=1064
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
  (func $realloc (type 7) (param i32 i32) (result i32)
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
  (func $free (type 8) (param i32)
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
  (func $__WASP_alloc (type 7) (param i32 i32) (result i32)
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
  (func $__WASP_dealloc (type 8) (param i32)
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
  (func $__WASP_symb_int (type 0) (param i32) (result i32)
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
  (global $__stack_pointer (mut i32) (i32.const 66656))
  (export "memory" (memory 0))
  (export "__original_main" (func $__original_main))
  (data $.rodata (i32.const 1024) "t\00producao\00f\00capacidade\00%d\00c\00 \00%d %d\0a\00")
  (data $.data (i32.const 1064) "`\04\01\00"))
