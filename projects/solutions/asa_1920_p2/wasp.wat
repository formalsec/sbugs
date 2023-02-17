(module
  (type (;0;) (func (param i32 i32 i32) (result i32)))
  (type (;1;) (func (param i32 i32) (result i32)))
  (type (;2;) (func (param i32 i32 i32 i32) (result i32)))
  (type (;3;) (func (param i32 i32 i32)))
  (type (;4;) (func (param i32 i32 i32 i32)))
  (type (;5;) (func (param i32 i32 i32 i32 i32)))
  (type (;6;) (func (param i32 i32 i32 i32 i32 i32)))
  (type (;7;) (func (param i32) (result i32)))
  (type (;8;) (func (param i32)))
  (type (;9;) (func (result i32)))
  (func $insertBegin (type 1) (param i32 i32) (result i32)
    (local i32)
    global.get 0
    i32.const 16
    i32.sub
    local.tee 2
    global.set 0
    local.get 2
    local.get 0
    i32.store offset=12
    local.get 2
    local.get 1
    i32.store offset=8
    local.get 2
    i32.const 16
    call $malloc
    i32.store offset=4
    local.get 2
    i32.load offset=4
    local.get 2
    i32.load offset=12
    i32.store
    local.get 2
    i32.load offset=4
    i32.const 0
    i32.store offset=4
    local.get 2
    i32.load offset=4
    i32.const 1
    i32.store offset=8
    local.get 2
    i32.load offset=4
    local.get 2
    i32.load offset=8
    i32.store offset=12
    local.get 2
    i32.load offset=4
    local.set 0
    local.get 2
    i32.const 16
    i32.add
    global.set 0
    local.get 0)
  (func $insertEdge (type 0) (param i32 i32 i32) (result i32)
    (local i32)
    global.get 0
    i32.const 32
    i32.sub
    local.tee 3
    global.set 0
    local.get 3
    local.get 0
    i32.store offset=24
    local.get 3
    local.get 1
    i32.store offset=20
    local.get 3
    local.get 2
    i32.store offset=16
    local.get 3
    local.get 3
    i32.load offset=24
    i32.load offset=12
    local.get 3
    i32.load offset=20
    i32.const 2
    i32.shl
    i32.add
    i32.load
    i32.store offset=12
    block  ;; label = @1
      block  ;; label = @2
        loop  ;; label = @3
          local.get 3
          i32.load offset=12
          i32.const 0
          i32.ne
          i32.const 1
          i32.and
          i32.eqz
          br_if 1 (;@2;)
          block  ;; label = @4
            local.get 3
            i32.load offset=12
            i32.load
            local.get 3
            i32.load offset=16
            i32.eq
            i32.const 1
            i32.and
            i32.eqz
            br_if 0 (;@4;)
            block  ;; label = @5
              local.get 3
              i32.load offset=12
              i32.load offset=4
              local.get 3
              i32.load offset=12
              i32.load offset=8
              i32.eq
              i32.const 1
              i32.and
              i32.eqz
              br_if 0 (;@5;)
              local.get 3
              i32.load offset=12
              local.tee 0
              local.get 0
              i32.load offset=4
              local.get 3
              i32.load offset=12
              i32.load offset=8
              i32.sub
              i32.store offset=4
            end
            local.get 3
            i32.const 0
            i32.store offset=28
            br 3 (;@1;)
          end
          local.get 3
          local.get 3
          i32.load offset=12
          i32.load offset=12
          i32.store offset=12
          br 0 (;@3;)
        end
      end
      local.get 3
      i32.load offset=16
      local.get 3
      i32.load offset=24
      i32.load offset=12
      local.get 3
      i32.load offset=20
      i32.const 2
      i32.shl
      i32.add
      i32.load
      call $insertBegin
      local.set 0
      local.get 3
      i32.load offset=24
      i32.load offset=12
      local.get 3
      i32.load offset=20
      i32.const 2
      i32.shl
      i32.add
      local.get 0
      i32.store
      local.get 3
      i32.const 1
      i32.store offset=28
    end
    local.get 3
    i32.load offset=28
    local.set 0
    local.get 3
    i32.const 32
    i32.add
    global.set 0
    local.get 0)
  (func $graphInit (type 1) (param i32 i32) (result i32)
    (local i32)
    global.get 0
    i32.const 16
    i32.sub
    local.tee 2
    global.set 0
    local.get 2
    local.get 0
    i32.store offset=12
    local.get 2
    local.get 1
    i32.store offset=8
    local.get 2
    i32.const 16
    call $malloc
    i32.store
    local.get 2
    i32.load
    local.get 2
    i32.load offset=12
    local.get 2
    i32.load offset=8
    i32.mul
    i32.const 1
    i32.shl
    i32.const 2
    i32.add
    i32.store
    local.get 2
    i32.load
    local.get 2
    i32.load
    i32.load
    i32.const 2
    i32.sub
    i32.store offset=4
    local.get 2
    i32.load
    local.get 2
    i32.load
    i32.load
    i32.const 1
    i32.sub
    i32.store offset=8
    local.get 2
    i32.load
    i32.load
    i32.const 2
    i32.shl
    call $malloc
    local.set 0
    local.get 2
    i32.load
    local.get 0
    i32.store offset=12
    local.get 2
    i32.const 0
    i32.store offset=4
    block  ;; label = @1
      loop  ;; label = @2
        local.get 2
        i32.load offset=4
        local.get 2
        i32.load
        i32.load
        i32.lt_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        local.get 2
        i32.load
        i32.load offset=12
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
    local.get 2
    i32.load
    local.set 0
    local.get 2
    i32.const 16
    i32.add
    global.set 0
    local.get 0)
  (func $whichVertex (type 2) (param i32 i32 i32 i32) (result i32)
    (local i32)
    global.get 0
    i32.const 16
    i32.sub
    local.tee 4
    local.get 0
    i32.store offset=12
    local.get 4
    local.get 1
    i32.store offset=8
    local.get 4
    local.get 2
    i32.store offset=4
    local.get 4
    local.get 3
    i32.store
    local.get 4
    i32.load
    local.get 4
    i32.load offset=4
    i32.mul
    local.get 4
    i32.load
    local.get 4
    i32.load offset=8
    i32.sub
    i32.const 1
    i32.add
    i32.sub)
  (func $buildRoads (type 3) (param i32 i32 i32)
    (local i32)
    global.get 0
    i32.const 32
    i32.sub
    local.tee 3
    global.set 0
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
    i32.const 1
    i32.store offset=16
    block  ;; label = @1
      loop  ;; label = @2
        local.get 3
        i32.load offset=16
        local.get 3
        i32.load offset=20
        i32.le_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        local.get 3
        i32.const 1
        i32.store offset=12
        block  ;; label = @3
          loop  ;; label = @4
            local.get 3
            i32.load offset=12
            local.get 3
            i32.load offset=24
            i32.le_s
            i32.const 1
            i32.and
            i32.eqz
            br_if 1 (;@3;)
            local.get 3
            local.get 3
            i32.load offset=28
            local.get 3
            i32.load offset=12
            local.get 3
            i32.load offset=16
            local.get 3
            i32.load offset=24
            call $whichVertex
            i32.store offset=8
            block  ;; label = @5
              local.get 3
              i32.load offset=12
              i32.const 1
              i32.add
              local.get 3
              i32.load offset=24
              i32.le_s
              i32.const 1
              i32.and
              i32.eqz
              br_if 0 (;@5;)
              local.get 3
              local.get 3
              i32.load offset=28
              local.get 3
              i32.load offset=12
              i32.const 1
              i32.add
              local.get 3
              i32.load offset=16
              local.get 3
              i32.load offset=24
              call $whichVertex
              i32.store offset=4
              local.get 3
              i32.load offset=28
              local.get 3
              i32.load offset=8
              local.get 3
              i32.load offset=24
              local.get 3
              i32.load offset=20
              i32.mul
              i32.add
              local.get 3
              i32.load offset=4
              call $insertEdge
              drop
              local.get 3
              i32.load offset=28
              local.get 3
              i32.load offset=4
              local.get 3
              i32.load offset=24
              local.get 3
              i32.load offset=20
              i32.mul
              i32.add
              local.get 3
              i32.load offset=8
              call $insertEdge
              drop
            end
            block  ;; label = @5
              local.get 3
              i32.load offset=16
              i32.const 1
              i32.add
              local.get 3
              i32.load offset=20
              i32.le_s
              i32.const 1
              i32.and
              i32.eqz
              br_if 0 (;@5;)
              local.get 3
              local.get 3
              i32.load offset=28
              local.get 3
              i32.load offset=12
              local.get 3
              i32.load offset=16
              i32.const 1
              i32.add
              local.get 3
              i32.load offset=24
              call $whichVertex
              i32.store offset=4
              local.get 3
              i32.load offset=28
              local.get 3
              i32.load offset=8
              local.get 3
              i32.load offset=24
              local.get 3
              i32.load offset=20
              i32.mul
              i32.add
              local.get 3
              i32.load offset=4
              call $insertEdge
              drop
              local.get 3
              i32.load offset=28
              local.get 3
              i32.load offset=4
              local.get 3
              i32.load offset=24
              local.get 3
              i32.load offset=20
              i32.mul
              i32.add
              local.get 3
              i32.load offset=8
              call $insertEdge
              drop
            end
            local.get 3
            i32.load offset=28
            local.get 3
            i32.load offset=8
            local.get 3
            i32.load offset=8
            local.get 3
            i32.load offset=24
            local.get 3
            i32.load offset=20
            i32.mul
            i32.add
            call $insertEdge
            drop
            local.get 3
            local.get 3
            i32.load offset=12
            i32.const 1
            i32.add
            i32.store offset=12
            br 0 (;@4;)
          end
        end
        local.get 3
        local.get 3
        i32.load offset=16
        i32.const 1
        i32.add
        i32.store offset=16
        br 0 (;@2;)
      end
    end
    local.get 3
    i32.const 32
    i32.add
    global.set 0)
  (func $addCitizen (type 4) (param i32 i32 i32 i32)
    (local i32)
    global.get 0
    i32.const 32
    i32.sub
    local.tee 4
    global.set 0
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
    local.get 4
    local.get 4
    i32.load offset=28
    local.get 4
    i32.load offset=24
    local.get 4
    i32.load offset=20
    local.get 4
    i32.load offset=16
    call $whichVertex
    i32.store offset=12
    local.get 4
    i32.load offset=28
    local.get 4
    i32.load offset=28
    i32.load offset=4
    local.get 4
    i32.load offset=12
    call $insertEdge
    drop
    local.get 4
    i32.const 32
    i32.add
    global.set 0)
  (func $addSupermarkets (type 5) (param i32 i32 i32 i32 i32)
    (local i32)
    global.get 0
    i32.const 32
    i32.sub
    local.tee 5
    global.set 0
    local.get 5
    local.get 0
    i32.store offset=28
    local.get 5
    local.get 1
    i32.store offset=24
    local.get 5
    local.get 2
    i32.store offset=20
    local.get 5
    local.get 3
    i32.store offset=16
    local.get 5
    local.get 4
    i32.store offset=12
    local.get 5
    local.get 5
    i32.load offset=28
    local.get 5
    i32.load offset=24
    local.get 5
    i32.load offset=20
    local.get 5
    i32.load offset=16
    call $whichVertex
    i32.store offset=8
    local.get 5
    i32.load offset=28
    local.get 5
    i32.load offset=8
    local.get 5
    i32.load offset=16
    local.get 5
    i32.load offset=12
    i32.mul
    i32.add
    local.get 5
    i32.load offset=28
    i32.load offset=8
    call $insertEdge
    drop
    local.get 5
    i32.const 32
    i32.add
    global.set 0)
  (func $addingCitizenAndSupermarkets (type 6) (param i32 i32 i32 i32 i32 i32)
    (local i32)
    global.get 0
    i32.const 48
    i32.sub
    local.tee 6
    global.set 0
    local.get 6
    local.get 0
    i32.store offset=44
    local.get 6
    local.get 1
    i32.store offset=40
    local.get 6
    local.get 2
    i32.store offset=36
    local.get 6
    local.get 3
    i32.store offset=32
    local.get 6
    local.get 4
    i32.store offset=28
    local.get 6
    local.get 5
    i32.store offset=24
    local.get 6
    i32.const 0
    i32.store offset=12
    block  ;; label = @1
      loop  ;; label = @2
        local.get 6
        i32.load offset=12
        local.get 6
        i32.load offset=40
        i32.lt_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        local.get 6
        i32.const 1051
        i32.symbolic
        i32.store offset=20
        local.get 6
        i32.const 1046
        i32.symbolic
        i32.store offset=16
        local.get 6
        i32.load offset=44
        local.get 6
        i32.load offset=20
        local.get 6
        i32.load offset=16
        local.get 6
        i32.load offset=32
        local.get 6
        i32.load offset=28
        call $addSupermarkets
        local.get 6
        local.get 6
        i32.load offset=12
        i32.const 1
        i32.add
        i32.store offset=12
        br 0 (;@2;)
      end
    end
    local.get 6
    i32.const 0
    i32.store offset=12
    block  ;; label = @1
      loop  ;; label = @2
        local.get 6
        i32.load offset=12
        local.get 6
        i32.load offset=36
        i32.lt_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        local.get 6
        i32.const 1051
        i32.symbolic
        i32.store offset=20
        local.get 6
        i32.const 1046
        i32.symbolic
        i32.store offset=16
        local.get 6
        i32.load offset=44
        local.get 6
        i32.load offset=20
        local.get 6
        i32.load offset=16
        local.get 6
        i32.load offset=32
        call $addCitizen
        local.get 6
        local.get 6
        i32.load offset=12
        i32.const 1
        i32.add
        i32.store offset=12
        br 0 (;@2;)
      end
    end
    local.get 6
    i32.const 48
    i32.add
    global.set 0)
  (func $QUEUEempty (type 7) (param i32) (result i32)
    (local i32)
    global.get 0
    i32.const 16
    i32.sub
    local.tee 1
    local.get 0
    i32.store offset=12
    local.get 1
    i32.load offset=12
    i32.load
    i32.const 0
    i32.eq
    i32.const 1
    i32.and)
  (func $QUEUEput (type 3) (param i32 i32 i32)
    (local i32)
    global.get 0
    i32.const 16
    i32.sub
    local.tee 3
    global.set 0
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
        i32.load offset=12
        i32.load
        i32.const 0
        i32.eq
        i32.const 1
        i32.and
        i32.eqz
        br_if 0 (;@2;)
        local.get 3
        i32.load offset=4
        local.get 3
        i32.load offset=12
        i32.load
        call $insertBegin
        local.set 0
        local.get 3
        i32.load offset=8
        local.get 0
        i32.store
        local.get 3
        i32.load offset=12
        local.get 0
        i32.store
        br 1 (;@1;)
      end
      local.get 3
      i32.load offset=4
      local.get 3
      i32.load offset=8
      i32.load
      i32.load offset=12
      call $insertBegin
      local.set 0
      local.get 3
      i32.load offset=8
      i32.load
      local.get 0
      i32.store offset=12
      local.get 3
      i32.load offset=8
      local.get 3
      i32.load offset=8
      i32.load
      i32.load offset=12
      i32.store
    end
    local.get 3
    i32.const 16
    i32.add
    global.set 0)
  (func $QUEUEget (type 7) (param i32) (result i32)
    (local i32)
    global.get 0
    i32.const 16
    i32.sub
    local.tee 1
    global.set 0
    local.get 1
    local.get 0
    i32.store offset=12
    local.get 1
    local.get 1
    i32.load offset=12
    i32.load
    i32.load
    i32.store offset=8
    local.get 1
    local.get 1
    i32.load offset=12
    i32.load
    i32.load offset=12
    i32.store offset=4
    local.get 1
    i32.load offset=12
    i32.load
    call $free
    local.get 1
    i32.load offset=12
    local.get 1
    i32.load offset=4
    i32.store
    local.get 1
    i32.load offset=8
    local.set 0
    local.get 1
    i32.const 16
    i32.add
    global.set 0
    local.get 0)
  (func $freeQUEUE (type 8) (param i32)
    (local i32)
    global.get 0
    i32.const 16
    i32.sub
    local.tee 1
    global.set 0
    local.get 1
    local.get 0
    i32.store offset=12
    block  ;; label = @1
      loop  ;; label = @2
        local.get 1
        i32.load offset=12
        i32.load
        i32.const 0
        i32.ne
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        local.get 1
        local.get 1
        i32.load offset=12
        i32.load
        i32.load offset=12
        i32.store offset=8
        local.get 1
        i32.load offset=12
        i32.load
        call $free
        local.get 1
        i32.load offset=12
        local.get 1
        i32.load offset=8
        i32.store
        br 0 (;@2;)
      end
    end
    local.get 1
    i32.const 16
    i32.add
    global.set 0)
  (func $BFS (type 0) (param i32 i32 i32) (result i32)
    (local i32)
    global.get 0
    i32.const 48
    i32.sub
    local.tee 3
    global.set 0
    local.get 3
    local.get 0
    i32.store offset=40
    local.get 3
    local.get 1
    i32.store offset=36
    local.get 3
    local.get 2
    i32.store offset=32
    local.get 3
    i32.const 0
    i32.store offset=28
    local.get 3
    i32.const 0
    i32.store offset=24
    local.get 3
    local.get 3
    i32.load offset=40
    i32.load
    i32.const 2
    i32.shl
    call $malloc
    i32.store offset=20
    local.get 3
    i32.load offset=32
    i32.const -1
    local.get 3
    i32.load offset=40
    i32.load
    i32.const 2
    i32.shl
    call $memset
    drop
    local.get 3
    i32.load offset=20
    i32.const 0
    local.get 3
    i32.load offset=40
    i32.load
    i32.const 2
    i32.shl
    call $memset
    drop
    local.get 3
    i32.load offset=32
    local.get 3
    i32.load offset=36
    i32.const 2
    i32.shl
    i32.add
    i32.const -2
    i32.store
    local.get 3
    i32.const 28
    i32.add
    local.get 3
    i32.const 24
    i32.add
    local.get 3
    i32.load offset=36
    call $QUEUEput
    block  ;; label = @1
      block  ;; label = @2
        loop  ;; label = @3
          local.get 3
          i32.const 28
          i32.add
          call $QUEUEempty
          i32.const 0
          i32.ne
          i32.const -1
          i32.xor
          i32.const 1
          i32.and
          i32.eqz
          br_if 1 (;@2;)
          local.get 3
          local.get 3
          i32.const 28
          i32.add
          call $QUEUEget
          i32.store offset=12
          local.get 3
          local.get 3
          i32.load offset=40
          i32.load offset=12
          local.get 3
          i32.load offset=12
          i32.const 2
          i32.shl
          i32.add
          i32.load
          i32.store offset=16
          block  ;; label = @4
            loop  ;; label = @5
              local.get 3
              i32.load offset=16
              i32.const 0
              i32.ne
              i32.const 1
              i32.and
              i32.eqz
              br_if 1 (;@4;)
              local.get 3
              local.get 3
              i32.load offset=16
              i32.load
              i32.store offset=8
              block  ;; label = @6
                local.get 3
                i32.load offset=20
                local.get 3
                i32.load offset=8
                i32.const 2
                i32.shl
                i32.add
                i32.load
                br_if 0 (;@6;)
                local.get 3
                i32.load offset=16
                i32.load offset=8
                local.get 3
                i32.load offset=16
                i32.load offset=4
                i32.sub
                i32.const 0
                i32.gt_s
                i32.const 1
                i32.and
                i32.eqz
                br_if 0 (;@6;)
                local.get 3
                i32.load offset=32
                local.get 3
                i32.load offset=8
                i32.const 2
                i32.shl
                i32.add
                local.get 3
                i32.load offset=12
                i32.store
                block  ;; label = @7
                  local.get 3
                  i32.load offset=8
                  local.get 3
                  i32.load offset=40
                  i32.load offset=8
                  i32.eq
                  i32.const 1
                  i32.and
                  i32.eqz
                  br_if 0 (;@7;)
                  local.get 3
                  i32.load offset=20
                  call $free
                  local.get 3
                  i32.const 28
                  i32.add
                  call $freeQUEUE
                  local.get 3
                  local.get 3
                  i32.load offset=32
                  i32.store offset=44
                  br 6 (;@1;)
                end
                local.get 3
                i32.load offset=20
                local.get 3
                i32.load offset=8
                i32.const 2
                i32.shl
                i32.add
                i32.const 1
                i32.store
                local.get 3
                i32.const 28
                i32.add
                local.get 3
                i32.const 24
                i32.add
                local.get 3
                i32.load offset=8
                call $QUEUEput
              end
              local.get 3
              local.get 3
              i32.load offset=16
              i32.load offset=12
              i32.store offset=16
              br 0 (;@5;)
            end
          end
          local.get 3
          i32.load offset=20
          local.get 3
          i32.load offset=12
          i32.const 2
          i32.shl
          i32.add
          i32.const 2
          i32.store
          br 0 (;@3;)
        end
      end
      local.get 3
      i32.load offset=20
      call $free
      local.get 3
      local.get 3
      i32.load offset=32
      i32.store offset=44
    end
    local.get 3
    i32.load offset=44
    local.set 0
    local.get 3
    i32.const 48
    i32.add
    global.set 0
    local.get 0)
  (func $edmondsKarp (type 7) (param i32) (result i32)
    (local i32)
    global.get 0
    i32.const 32
    i32.sub
    local.tee 1
    global.set 0
    local.get 1
    local.get 0
    i32.store offset=28
    local.get 1
    i32.const 0
    i32.store offset=24
    local.get 1
    local.get 1
    i32.load offset=28
    i32.load
    i32.const 2
    i32.shl
    call $malloc
    i32.store offset=20
    block  ;; label = @1
      loop  ;; label = @2
        local.get 1
        local.get 1
        i32.load offset=28
        local.get 1
        i32.load offset=28
        i32.load offset=4
        local.get 1
        i32.load offset=20
        call $BFS
        i32.store offset=20
        block  ;; label = @3
          local.get 1
          i32.load offset=20
          local.get 1
          i32.load offset=28
          i32.load offset=8
          i32.const 2
          i32.shl
          i32.add
          i32.load
          i32.const -1
          i32.eq
          i32.const 1
          i32.and
          i32.eqz
          br_if 0 (;@3;)
          br 2 (;@1;)
        end
        local.get 1
        local.get 1
        i32.load offset=28
        i32.load offset=8
        i32.store offset=16
        block  ;; label = @3
          loop  ;; label = @4
            local.get 1
            i32.load offset=20
            local.get 1
            i32.load offset=16
            i32.const 2
            i32.shl
            i32.add
            i32.load
            i32.const -2
            i32.ne
            i32.const 1
            i32.and
            i32.eqz
            br_if 1 (;@3;)
            local.get 1
            local.get 1
            i32.load offset=28
            i32.load offset=12
            local.get 1
            i32.load offset=20
            local.get 1
            i32.load offset=16
            i32.const 2
            i32.shl
            i32.add
            i32.load
            i32.const 2
            i32.shl
            i32.add
            i32.load
            i32.store offset=12
            block  ;; label = @5
              loop  ;; label = @6
                local.get 1
                i32.load offset=12
                i32.const 0
                i32.ne
                i32.const 1
                i32.and
                i32.eqz
                br_if 1 (;@5;)
                block  ;; label = @7
                  local.get 1
                  i32.load offset=12
                  i32.load
                  local.get 1
                  i32.load offset=16
                  i32.eq
                  i32.const 1
                  i32.and
                  i32.eqz
                  br_if 0 (;@7;)
                  local.get 1
                  i32.load offset=12
                  local.tee 0
                  local.get 0
                  i32.load offset=4
                  local.get 1
                  i32.load offset=12
                  i32.load offset=8
                  i32.add
                  i32.store offset=4
                end
                local.get 1
                local.get 1
                i32.load offset=12
                i32.load offset=12
                i32.store offset=12
                br 0 (;@6;)
              end
            end
            local.get 1
            i32.load offset=28
            local.get 1
            i32.load offset=16
            local.get 1
            i32.load offset=20
            local.get 1
            i32.load offset=16
            i32.const 2
            i32.shl
            i32.add
            i32.load
            call $insertEdge
            drop
            local.get 1
            local.get 1
            i32.load offset=20
            local.get 1
            i32.load offset=16
            i32.const 2
            i32.shl
            i32.add
            i32.load
            i32.store offset=16
            br 0 (;@4;)
          end
        end
        local.get 1
        local.get 1
        i32.load offset=24
        i32.const 1
        i32.add
        i32.store offset=24
        br 0 (;@2;)
      end
    end
    local.get 1
    i32.load offset=20
    call $free
    local.get 1
    i32.load offset=24
    local.set 0
    local.get 1
    i32.const 32
    i32.add
    global.set 0
    local.get 0)
  (func $freeCity (type 8) (param i32)
    (local i32)
    global.get 0
    i32.const 16
    i32.sub
    local.tee 1
    global.set 0
    local.get 1
    local.get 0
    i32.store offset=12
    local.get 1
    i32.const 0
    i32.store offset=8
    block  ;; label = @1
      loop  ;; label = @2
        local.get 1
        i32.load offset=8
        local.get 1
        i32.load offset=12
        i32.load
        i32.lt_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        block  ;; label = @3
          loop  ;; label = @4
            local.get 1
            i32.load offset=12
            i32.load offset=12
            local.get 1
            i32.load offset=8
            i32.const 2
            i32.shl
            i32.add
            i32.load
            i32.const 0
            i32.ne
            i32.const 1
            i32.and
            i32.eqz
            br_if 1 (;@3;)
            local.get 1
            local.get 1
            i32.load offset=12
            i32.load offset=12
            local.get 1
            i32.load offset=8
            i32.const 2
            i32.shl
            i32.add
            i32.load
            i32.store offset=4
            local.get 1
            i32.load offset=12
            i32.load offset=12
            local.get 1
            i32.load offset=8
            i32.const 2
            i32.shl
            i32.add
            local.get 1
            i32.load offset=12
            i32.load offset=12
            local.get 1
            i32.load offset=8
            i32.const 2
            i32.shl
            i32.add
            i32.load
            i32.load offset=12
            i32.store
            local.get 1
            i32.load offset=4
            call $free
            br 0 (;@4;)
          end
        end
        local.get 1
        local.get 1
        i32.load offset=8
        i32.const 1
        i32.add
        i32.store offset=8
        br 0 (;@2;)
      end
    end
    local.get 1
    i32.load offset=12
    i32.load offset=12
    call $free
    local.get 1
    i32.load offset=12
    call $free
    local.get 1
    i32.const 16
    i32.add
    global.set 0)
  (func $__original_main (type 9) (result i32)
    (local i32)
    global.get 0
    i32.const 144
    i32.sub
    local.tee 0
    global.set 0
    local.get 0
    i32.const 1042
    i32.symbolic
    i32.store offset=28
    local.get 0
    i32.const 1040
    i32.symbolic
    i32.store offset=24
    local.get 0
    local.get 0
    i32.load offset=28
    local.get 0
    i32.load offset=24
    call $graphInit
    i32.store offset=12
    local.get 0
    i32.load offset=12
    local.get 0
    i32.load offset=28
    local.get 0
    i32.load offset=24
    call $buildRoads
    local.get 0
    i32.const 1044
    i32.symbolic
    i32.store offset=20
    local.get 0
    i32.const 1038
    i32.symbolic
    i32.store offset=16
    local.get 0
    i32.load offset=12
    local.get 0
    i32.load offset=20
    local.get 0
    i32.load offset=16
    local.get 0
    i32.load offset=28
    local.get 0
    i32.load offset=24
    local.get 0
    i32.const 32
    i32.add
    call $addingCitizenAndSupermarkets
    local.get 0
    local.get 0
    i32.load offset=12
    call $edmondsKarp
    i32.store
    i32.const 1056
    local.get 0
    call $printf
    drop
    local.get 0
    i32.load offset=12
    call $freeCity
    local.get 0
    i32.const 144
    i32.add
    global.set 0
    i32.const 0)
  (func $printf (type 1) (param i32 i32) (result i32)
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
  (func $summ_not_implemented_error (type 8) (param i32)
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
  (func $summ_maximize (type 1) (param i32 i32) (result i32)
    (local i32 i32 i32 i32 i32 i32 i32)
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
    i32.const 1024
    local.set 5
    local.get 5
    call $summ_not_implemented_error
    i32.const 0
    local.set 6
    i32.const 16
    local.set 7
    local.get 4
    local.get 7
    i32.add
    local.set 8
    local.get 8
    global.set 0
    local.get 6
    return)
  (func $summ_is_symbolic (type 1) (param i32 i32) (result i32)
    (local i32 i32 i32 i32 i32 i32 i32 i32)
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
    local.get 4
    i32.load offset=12
    local.set 5
    local.get 4
    i32.load offset=8
    local.set 6
    local.get 5
    local.get 6
    is_symbolic
    local.set 7
    i32.const 16
    local.set 8
    local.get 4
    local.get 8
    i32.add
    local.set 9
    local.get 9
    global.set 0
    local.get 7
    return)
  (func $malloc (type 7) (param i32) (result i32)
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
    i32.load offset=1060
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
    i32.load offset=1060
    local.set 8
    local.get 8
    local.get 6
    i32.add
    local.set 9
    i32.const 0
    local.set 10
    local.get 10
    local.get 9
    i32.store offset=1060
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
  (func $free (type 8) (param i32)
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
  (func $memset1 (type 0) (param i32 i32 i32) (result i32)
    (local i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32)
    global.get 0
    local.set 3
    i32.const 32
    local.set 4
    local.get 3
    local.get 4
    i32.sub
    local.set 5
    local.get 5
    global.set 0
    local.get 5
    local.get 0
    i32.store offset=28
    local.get 5
    local.get 1
    i32.store offset=24
    local.get 5
    local.get 2
    i32.store offset=20
    local.get 5
    i32.load offset=28
    local.set 6
    local.get 5
    local.get 6
    i32.store offset=16
    local.get 5
    i32.load offset=24
    local.set 7
    local.get 5
    local.get 7
    i32.store8 offset=15
    i32.const 20
    local.set 8
    local.get 5
    local.get 8
    i32.add
    local.set 9
    local.get 9
    local.set 10
    i32.const 32
    local.set 11
    local.get 10
    local.get 11
    call $summ_is_symbolic
    local.set 12
    block  ;; label = @1
      local.get 12
      i32.eqz
      br_if 0 (;@1;)
      i32.const 20
      local.set 13
      local.get 5
      local.get 13
      i32.add
      local.set 14
      local.get 14
      local.set 15
      i32.const 32
      local.set 16
      local.get 15
      local.get 16
      call $summ_maximize
      local.set 17
      local.get 17
      i32.load
      local.set 18
      local.get 5
      local.get 18
      i32.store offset=20
    end
    i32.const 0
    local.set 19
    local.get 5
    local.get 19
    i32.store offset=8
    block  ;; label = @1
      loop  ;; label = @2
        local.get 5
        i32.load offset=8
        local.set 20
        local.get 5
        i32.load offset=20
        local.set 21
        local.get 20
        local.set 22
        local.get 21
        local.set 23
        local.get 22
        local.get 23
        i32.lt_s
        local.set 24
        i32.const 1
        local.set 25
        local.get 24
        local.get 25
        i32.and
        local.set 26
        local.get 26
        i32.eqz
        br_if 1 (;@1;)
        local.get 5
        i32.load8_u offset=15
        local.set 27
        local.get 5
        i32.load offset=16
        local.set 28
        local.get 5
        i32.load offset=8
        local.set 29
        local.get 28
        local.get 29
        i32.add
        local.set 30
        local.get 30
        local.get 27
        i32.store8
        local.get 5
        i32.load offset=8
        local.set 31
        i32.const 1
        local.set 32
        local.get 31
        local.get 32
        i32.add
        local.set 33
        local.get 5
        local.get 33
        i32.store offset=8
        br 0 (;@2;)
      end
    end
    local.get 5
    i32.load offset=28
    local.set 34
    i32.const 32
    local.set 35
    local.get 5
    local.get 35
    i32.add
    local.set 36
    local.get 36
    global.set 0
    local.get 34
    return)
  (func $memset (type 0) (param i32 i32 i32) (result i32)
    (local i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32)
    global.get 0
    local.set 3
    i32.const 16
    local.set 4
    local.get 3
    local.get 4
    i32.sub
    local.set 5
    local.get 5
    global.set 0
    local.get 5
    local.get 0
    i32.store offset=12
    local.get 5
    local.get 1
    i32.store offset=8
    local.get 5
    local.get 2
    i32.store offset=4
    i32.const 0
    local.set 6
    local.get 6
    i32.load offset=1064
    local.set 7
    local.get 5
    i32.load offset=12
    local.set 8
    local.get 5
    i32.load offset=8
    local.set 9
    local.get 5
    i32.load offset=4
    local.set 10
    local.get 8
    local.get 9
    local.get 10
    local.get 7
    call_indirect (type 0)
    local.set 11
    i32.const 16
    local.set 12
    local.get 5
    local.get 12
    i32.add
    local.set 13
    local.get 13
    global.set 0
    local.get 11
    return)
  (func $__WASP_alloc (type 1) (param i32 i32) (result i32)
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
  (func $__WASP_dealloc (type 8) (param i32)
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
  (func $__WASP_symb_int (type 7) (param i32) (result i32)
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
  (func $__WASP_is_symbolic (type 1) (param i32 i32) (result i32)
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
    i32.const 0
    local.set 5
    local.get 5
    return)
  (table (;0;) 2 2 funcref)
  (memory (;0;) 2)
  (global (;0;) (mut i32) (i32.const 66608))
  (export "memory" (memory 0))
  (export "__original_main" (func $__original_main))
  (elem (;0;) (i32.const 1) $memset1)
  (data (;0;) (i32.const 1024) "summ_maximize\00S\00N\00M\00C\00num2\00num1\00%d\0a\00")
  (data (;1;) (i32.const 1060) "0\04\01\00\01\00\00\00"))
