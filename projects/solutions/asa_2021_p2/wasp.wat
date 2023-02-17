(module
  (type (;0;) (func (param i32) (result i32)))
  (type (;1;) (func (param i32)))
  (type (;2;) (func (param i32 i32 i32 i32) (result i32)))
  (type (;3;) (func (param i32 i32 i32 i32)))
  (type (;4;) (func (result i32)))
  (type (;5;) (func (param i32 i32)))
  (type (;6;) (func (param i32 i32 i32) (result i32)))
  (type (;7;) (func (param i32 i32) (result i32)))
  (func $newGraph (type 0) (param i32) (result i32)
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
    i32.const 8
    call $malloc
    i32.store offset=4
    local.get 1
    i32.load offset=4
    local.get 1
    i32.load offset=12
    i32.store
    local.get 1
    i32.load offset=4
    i32.load
    i32.const 3
    i32.shl
    call $malloc
    local.set 0
    local.get 1
    i32.load offset=4
    local.get 0
    i32.store offset=4
    local.get 1
    local.get 1
    i32.load offset=4
    i32.load offset=4
    i32.store
    local.get 1
    i32.const 0
    i32.store offset=8
    block  ;; label = @1
      loop  ;; label = @2
        local.get 1
        i32.load offset=8
        local.get 1
        i32.load offset=4
        i32.load
        i32.lt_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        local.get 1
        i32.load
        local.get 1
        i32.load offset=8
        i32.const 3
        i32.shl
        i32.add
        i32.const 0
        i32.store
        local.get 1
        i32.load
        local.get 1
        i32.load offset=8
        i32.const 3
        i32.shl
        i32.add
        i32.const 0
        i32.store offset=4
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
    i32.load offset=4
    local.set 0
    local.get 1
    i32.const 16
    i32.add
    global.set 0
    local.get 0)
  (func $freeGraph (type 1) (param i32)
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
    block  ;; label = @1
      loop  ;; label = @2
        local.get 1
        i32.load offset=24
        local.get 1
        i32.load offset=28
        i32.load
        i32.lt_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        local.get 1
        local.get 1
        i32.load offset=28
        i32.load offset=4
        local.get 1
        i32.load offset=24
        i32.const 3
        i32.shl
        i32.add
        i32.store offset=20
        local.get 1
        local.get 1
        i32.load offset=20
        i32.load
        i32.store offset=16
        block  ;; label = @3
          loop  ;; label = @4
            local.get 1
            i32.load offset=16
            i32.const 0
            i32.ne
            i32.const 1
            i32.and
            i32.eqz
            br_if 1 (;@3;)
            local.get 1
            local.get 1
            i32.load offset=16
            i32.load offset=24
            i32.store offset=12
            local.get 1
            i32.load offset=16
            call $free
            local.get 1
            local.get 1
            i32.load offset=12
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
    i32.load offset=28
    i32.load offset=4
    call $free
    local.get 1
    i32.load offset=28
    call $free
    local.get 1
    i32.const 32
    i32.add
    global.set 0)
  (func $newNode (type 2) (param i32 i32 i32 i32) (result i32)
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
    i32.load offset=4
    local.get 4
    i32.load offset=24
    i32.const 3
    i32.shl
    i32.add
    i32.store offset=12
    local.get 4
    i32.const 28
    call $malloc
    i32.store offset=8
    local.get 4
    i32.load offset=8
    local.get 4
    i32.load offset=20
    i32.store
    local.get 4
    i32.load offset=8
    local.get 4
    i32.load offset=24
    i32.store offset=4
    local.get 4
    i32.load offset=8
    local.get 4
    i32.load offset=16
    i32.store offset=12
    local.get 4
    i32.load offset=8
    i32.const 0
    i32.store offset=8
    local.get 4
    i32.load offset=8
    local.get 4
    i32.load offset=16
    i32.store offset=16
    local.get 4
    i32.load offset=8
    i32.const 0
    i32.store offset=20
    local.get 4
    i32.load offset=8
    i32.const 0
    i32.store offset=24
    block  ;; label = @1
      block  ;; label = @2
        local.get 4
        i32.load offset=12
        i32.load
        i32.const 0
        i32.eq
        i32.const 1
        i32.and
        i32.eqz
        br_if 0 (;@2;)
        local.get 4
        i32.load offset=12
        local.get 4
        i32.load offset=8
        i32.store
        br 1 (;@1;)
      end
      local.get 4
      i32.load offset=12
      i32.load offset=4
      local.get 4
      i32.load offset=8
      i32.store offset=24
    end
    local.get 4
    i32.load offset=12
    local.get 4
    i32.load offset=8
    i32.store offset=4
    local.get 4
    i32.load offset=8
    local.set 0
    local.get 4
    i32.const 32
    i32.add
    global.set 0
    local.get 0)
  (func $createProcessToProcessor (type 3) (param i32 i32 i32 i32)
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
    i32.const 0
    local.get 4
    i32.load offset=24
    local.get 4
    i32.load offset=20
    call $newNode
    i32.store offset=12
    local.get 4
    local.get 4
    i32.load offset=28
    local.get 4
    i32.load offset=24
    i32.const 0
    i32.const 0
    call $newNode
    i32.store offset=8
    local.get 4
    i32.load offset=12
    local.get 4
    i32.load offset=8
    i32.store offset=20
    local.get 4
    i32.load offset=8
    local.get 4
    i32.load offset=12
    i32.store offset=20
    local.get 4
    local.get 4
    i32.load offset=28
    local.get 4
    i32.load offset=24
    local.get 4
    i32.load offset=28
    i32.load
    i32.const 1
    i32.sub
    local.get 4
    i32.load offset=16
    call $newNode
    i32.store offset=12
    local.get 4
    local.get 4
    i32.load offset=28
    local.get 4
    i32.load offset=28
    i32.load
    i32.const 1
    i32.sub
    local.get 4
    i32.load offset=24
    local.get 4
    i32.load offset=16
    call $newNode
    i32.store offset=8
    local.get 4
    i32.load offset=12
    local.get 4
    i32.load offset=8
    i32.store offset=20
    local.get 4
    i32.load offset=8
    local.get 4
    i32.load offset=12
    i32.store offset=20
    local.get 4
    i32.const 32
    i32.add
    global.set 0)
  (func $createProcessToProcess (type 3) (param i32 i32 i32 i32)
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
    call $newNode
    i32.store offset=12
    local.get 4
    local.get 4
    i32.load offset=28
    local.get 4
    i32.load offset=20
    local.get 4
    i32.load offset=24
    local.get 4
    i32.load offset=16
    call $newNode
    i32.store offset=8
    local.get 4
    i32.load offset=12
    local.get 4
    i32.load offset=8
    i32.store offset=20
    local.get 4
    i32.load offset=8
    local.get 4
    i32.load offset=12
    i32.store offset=20
    local.get 4
    i32.const 32
    i32.add
    global.set 0)
  (func $newQueueEl (type 0) (param i32) (result i32)
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
    i32.const 8
    call $malloc
    i32.store offset=8
    local.get 1
    i32.load offset=8
    local.get 1
    i32.load offset=12
    i32.store
    local.get 1
    i32.load offset=8
    i32.const 0
    i32.store offset=4
    local.get 1
    i32.load offset=8
    local.set 0
    local.get 1
    i32.const 16
    i32.add
    global.set 0
    local.get 0)
  (func $freeQueueEl (type 1) (param i32)
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
    i32.load offset=12
    call $free
    local.get 1
    i32.const 16
    i32.add
    global.set 0)
  (func $newQueue (type 4) (result i32)
    (local i32 i32)
    global.get 0
    i32.const 16
    i32.sub
    local.tee 0
    global.set 0
    local.get 0
    i32.const 8
    call $malloc
    i32.store offset=12
    local.get 0
    i32.load offset=12
    i32.const 0
    i32.store
    local.get 0
    i32.load offset=12
    i32.const 0
    i32.store offset=4
    local.get 0
    i32.load offset=12
    local.set 1
    local.get 0
    i32.const 16
    i32.add
    global.set 0
    local.get 1)
  (func $freeQueue (type 1) (param i32)
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
    i32.store offset=8
    block  ;; label = @1
      loop  ;; label = @2
        local.get 1
        i32.load offset=8
        i32.const 0
        i32.ne
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        local.get 1
        local.get 1
        i32.load offset=8
        i32.load offset=4
        i32.store offset=4
        local.get 1
        i32.load offset=8
        call $freeQueueEl
        local.get 1
        local.get 1
        i32.load offset=4
        i32.store offset=8
        br 0 (;@2;)
      end
    end
    local.get 1
    i32.load offset=12
    call $free
    local.get 1
    i32.const 16
    i32.add
    global.set 0)
  (func $isQueueEmpty (type 0) (param i32) (result i32)
    (local i32)
    global.get 0
    i32.const 16
    i32.sub
    local.tee 1
    local.get 0
    i32.store offset=8
    block  ;; label = @1
      block  ;; label = @2
        local.get 1
        i32.load offset=8
        i32.load
        i32.const 0
        i32.ne
        i32.const 1
        i32.and
        br_if 0 (;@2;)
        local.get 1
        i32.const -1
        i32.store offset=12
        br 1 (;@1;)
      end
      local.get 1
      i32.const 0
      i32.store offset=12
    end
    local.get 1
    i32.load offset=12)
  (func $enQueue (type 5) (param i32 i32)
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
    local.get 2
    i32.load offset=8
    call $newQueueEl
    i32.store offset=4
    block  ;; label = @1
      block  ;; label = @2
        local.get 2
        i32.load offset=12
        call $isQueueEmpty
        i32.eqz
        br_if 0 (;@2;)
        local.get 2
        i32.load offset=12
        local.get 2
        i32.load offset=4
        i32.store
        br 1 (;@1;)
      end
      local.get 2
      i32.load offset=12
      i32.load offset=4
      local.get 2
      i32.load offset=4
      i32.store offset=4
    end
    local.get 2
    i32.load offset=12
    local.get 2
    i32.load offset=4
    i32.store offset=4
    local.get 2
    i32.const 16
    i32.add
    global.set 0)
  (func $deQueue (type 0) (param i32) (result i32)
    (local i32)
    global.get 0
    i32.const 16
    i32.sub
    local.tee 1
    global.set 0
    local.get 1
    local.get 0
    i32.store offset=8
    block  ;; label = @1
      block  ;; label = @2
        local.get 1
        i32.load offset=8
        call $isQueueEmpty
        i32.eqz
        br_if 0 (;@2;)
        local.get 1
        i32.const 0
        i32.store offset=12
        br 1 (;@1;)
      end
      local.get 1
      local.get 1
      i32.load offset=8
      i32.load
      i32.store offset=4
      block  ;; label = @2
        block  ;; label = @3
          local.get 1
          i32.load offset=8
          i32.load
          i32.load offset=4
          i32.const 0
          i32.ne
          i32.const 1
          i32.and
          br_if 0 (;@3;)
          local.get 1
          i32.load offset=8
          i32.const 0
          i32.store
          local.get 1
          i32.load offset=8
          i32.const 0
          i32.store offset=4
          br 1 (;@2;)
        end
        local.get 1
        i32.load offset=8
        local.get 1
        i32.load offset=4
        i32.load offset=4
        i32.store
      end
      local.get 1
      local.get 1
      i32.load offset=4
      i32.load
      i32.store
      local.get 1
      i32.load offset=4
      call $freeQueueEl
      local.get 1
      local.get 1
      i32.load
      i32.store offset=12
    end
    local.get 1
    i32.load offset=12
    local.set 0
    local.get 1
    i32.const 16
    i32.add
    global.set 0
    local.get 0)
  (func $clearQueue (type 1) (param i32)
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
    i32.store offset=8
    block  ;; label = @1
      loop  ;; label = @2
        local.get 1
        i32.load offset=8
        i32.const 0
        i32.ne
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        local.get 1
        local.get 1
        i32.load offset=8
        i32.load offset=4
        i32.store offset=4
        local.get 1
        i32.load offset=8
        call $freeQueueEl
        local.get 1
        local.get 1
        i32.load offset=4
        i32.store offset=8
        br 0 (;@2;)
      end
    end
    local.get 1
    i32.load offset=12
    i32.const 0
    i32.store
    local.get 1
    i32.load offset=12
    i32.const 0
    i32.store offset=4
    local.get 1
    i32.const 16
    i32.add
    global.set 0)
  (func $bfs (type 2) (param i32 i32 i32 i32) (result i32)
    (local i32)
    global.get 0
    i32.const 48
    i32.sub
    local.tee 4
    global.set 0
    local.get 4
    local.get 0
    i32.store offset=40
    local.get 4
    local.get 1
    i32.store offset=36
    local.get 4
    local.get 2
    i32.store offset=32
    local.get 4
    local.get 3
    i32.store offset=28
    local.get 4
    i32.const 0
    i32.store offset=12
    local.get 4
    i32.const 0
    i32.store offset=20
    block  ;; label = @1
      loop  ;; label = @2
        local.get 4
        i32.load offset=20
        local.get 4
        i32.load offset=40
        i32.load
        i32.lt_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        i32.const 0
        i32.load offset=1064
        local.get 4
        i32.load offset=20
        i32.const 2
        i32.shl
        i32.add
        i32.const 0
        i32.store
        local.get 4
        local.get 4
        i32.load offset=20
        i32.const 1
        i32.add
        i32.store offset=20
        br 0 (;@2;)
      end
    end
    i32.const 0
    i32.load offset=1068
    local.get 4
    i32.load offset=36
    call $enQueue
    i32.const 0
    i32.load offset=1064
    local.get 4
    i32.load offset=36
    i32.const 2
    i32.shl
    i32.add
    i32.const 1
    i32.store
    block  ;; label = @1
      block  ;; label = @2
        loop  ;; label = @3
          i32.const 0
          i32.load offset=1068
          call $isQueueEmpty
          br_if 1 (;@2;)
          local.get 4
          i32.const 0
          i32.load offset=1068
          call $deQueue
          i32.store offset=24
          i32.const 0
          i32.load offset=1064
          local.get 4
          i32.load offset=24
          i32.const 2
          i32.shl
          i32.add
          i32.const 2
          i32.store
          local.get 4
          local.get 4
          i32.load offset=40
          i32.load offset=4
          local.get 4
          i32.load offset=24
          i32.const 3
          i32.shl
          i32.add
          i32.store offset=16
          local.get 4
          local.get 4
          i32.load offset=16
          i32.load
          i32.store offset=12
          block  ;; label = @4
            loop  ;; label = @5
              local.get 4
              i32.load offset=12
              i32.const 0
              i32.ne
              i32.const 1
              i32.and
              i32.eqz
              br_if 1 (;@4;)
              block  ;; label = @6
                i32.const 0
                i32.load offset=1064
                local.get 4
                i32.load offset=12
                i32.load
                i32.const 2
                i32.shl
                i32.add
                i32.load
                br_if 0 (;@6;)
                local.get 4
                i32.load offset=12
                i32.load offset=16
                i32.const 0
                i32.gt_s
                i32.const 1
                i32.and
                i32.eqz
                br_if 0 (;@6;)
                i32.const 0
                i32.load offset=1068
                local.get 4
                i32.load offset=12
                i32.load
                call $enQueue
                i32.const 0
                i32.load offset=1064
                local.get 4
                i32.load offset=12
                i32.load
                i32.const 2
                i32.shl
                i32.add
                i32.const 1
                i32.store
                local.get 4
                i32.load offset=32
                local.get 4
                i32.load offset=12
                i32.load
                i32.const 2
                i32.shl
                i32.add
                local.get 4
                i32.load offset=12
                i32.store
                block  ;; label = @7
                  local.get 4
                  i32.load offset=12
                  i32.load
                  local.get 4
                  i32.load offset=40
                  i32.load
                  i32.const 1
                  i32.sub
                  i32.eq
                  i32.const 1
                  i32.and
                  i32.eqz
                  br_if 0 (;@7;)
                  i32.const 0
                  i32.load offset=1068
                  call $clearQueue
                  local.get 4
                  i32.const 1
                  i32.store offset=44
                  br 6 (;@1;)
                end
              end
              local.get 4
              local.get 4
              i32.load offset=12
              i32.load offset=24
              i32.store offset=12
              br 0 (;@5;)
            end
          end
          br 0 (;@3;)
        end
      end
      local.get 4
      i32.const 0
      i32.store offset=44
    end
    local.get 4
    i32.load offset=44
    local.set 0
    local.get 4
    i32.const 48
    i32.add
    global.set 0
    local.get 0)
  (func $incrementFlow (type 6) (param i32 i32 i32) (result i32)
    (local i32)
    global.get 0
    i32.const 16
    i32.sub
    local.tee 3
    local.get 0
    i32.store offset=12
    local.get 3
    local.get 1
    i32.store offset=8
    local.get 3
    local.get 2
    i32.store offset=4
    local.get 3
    i32.load offset=8
    local.tee 0
    local.get 0
    i32.load offset=8
    local.get 3
    i32.load offset=4
    i32.add
    i32.store offset=8
    local.get 3
    i32.load offset=8
    local.get 3
    i32.load offset=8
    i32.load offset=12
    local.get 3
    i32.load offset=8
    i32.load offset=8
    i32.sub
    i32.store offset=16
    local.get 3
    i32.load offset=8
    i32.load offset=4)
  (func $maxFlowPath (type 7) (param i32 i32) (result i32)
    (local i32)
    global.get 0
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
    i32.store offset=20
    local.get 2
    local.get 2
    i32.load offset=28
    i32.load
    i32.const 1
    i32.sub
    i32.store offset=16
    local.get 2
    local.get 2
    i32.load offset=24
    local.get 2
    i32.load offset=16
    i32.const 2
    i32.shl
    i32.add
    i32.load
    i32.store offset=12
    loop  ;; label = @1
      block  ;; label = @2
        block  ;; label = @3
          local.get 2
          i32.load offset=20
          br_if 0 (;@3;)
          local.get 2
          local.get 2
          i32.load offset=12
          i32.load offset=16
          i32.store offset=20
          br 1 (;@2;)
        end
        block  ;; label = @3
          local.get 2
          i32.load offset=20
          local.get 2
          i32.load offset=12
          i32.load offset=16
          i32.gt_s
          i32.const 1
          i32.and
          i32.eqz
          br_if 0 (;@3;)
          local.get 2
          local.get 2
          i32.load offset=12
          i32.load offset=16
          i32.store offset=20
        end
      end
      local.get 2
      local.get 2
      i32.load offset=12
      i32.load offset=4
      i32.store offset=16
      local.get 2
      local.get 2
      i32.load offset=24
      local.get 2
      i32.load offset=16
      i32.const 2
      i32.shl
      i32.add
      i32.load
      i32.store offset=12
      local.get 2
      i32.load offset=16
      br_if 0 (;@1;)
    end
    local.get 2
    i32.load offset=20)
  (func $maxFlow (type 7) (param i32 i32) (result i32)
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
    local.get 2
    i32.const 0
    i32.store offset=16
    local.get 2
    i32.const 0
    i32.store offset=12
    block  ;; label = @1
      loop  ;; label = @2
        local.get 2
        i32.load offset=28
        i32.const 0
        local.get 2
        i32.load offset=24
        local.get 2
        i32.load offset=28
        i32.load
        i32.const 1
        i32.sub
        call $bfs
        i32.eqz
        br_if 1 (;@1;)
        local.get 2
        local.get 2
        i32.load offset=28
        i32.load
        i32.const 1
        i32.sub
        i32.store offset=20
        local.get 2
        local.get 2
        i32.load offset=28
        local.get 2
        i32.load offset=24
        call $maxFlowPath
        i32.store offset=12
        local.get 2
        local.get 2
        i32.load offset=16
        local.get 2
        i32.load offset=12
        i32.add
        i32.store offset=16
        loop  ;; label = @3
          local.get 2
          local.get 2
          i32.load offset=24
          local.get 2
          i32.load offset=20
          i32.const 2
          i32.shl
          i32.add
          i32.load
          i32.store offset=8
          local.get 2
          local.get 2
          i32.load offset=28
          local.get 2
          i32.load offset=8
          local.get 2
          i32.load offset=12
          call $incrementFlow
          i32.store offset=20
          local.get 2
          local.get 2
          i32.load offset=8
          i32.load offset=20
          i32.store offset=4
          local.get 2
          i32.load offset=28
          local.get 2
          i32.load offset=4
          i32.const 0
          local.get 2
          i32.load offset=12
          i32.sub
          call $incrementFlow
          drop
          local.get 2
          i32.load offset=20
          br_if 0 (;@3;)
        end
        br 0 (;@2;)
      end
    end
    local.get 2
    i32.load offset=16
    local.set 0
    local.get 2
    i32.const 32
    i32.add
    global.set 0
    local.get 0)
  (func $__original_main (type 4) (result i32)
    (local i32 i32 i32)
    global.get 0
    i32.const 48
    i32.sub
    local.tee 0
    global.set 0
    local.get 0
    local.tee 1
    i32.const 1024
    i32.symbolic
    i32.store offset=44
    local.get 1
    i32.const 1030
    i32.symbolic
    i32.store offset=40
    local.get 1
    local.get 1
    i32.load offset=44
    i32.const 2
    i32.add
    call $newGraph
    i32.store offset=20
    i32.const 0
    local.get 1
    i32.load offset=20
    i32.load
    i32.const 2
    i32.shl
    call $malloc
    i32.store offset=1064
    local.get 1
    i32.load offset=20
    i32.load
    local.set 2
    local.get 1
    local.get 0
    i32.store offset=16
    local.get 0
    local.get 2
    i32.const 2
    i32.shl
    i32.const 15
    i32.add
    i32.const -16
    i32.and
    i32.sub
    local.tee 0
    global.set 0
    local.get 1
    local.get 2
    i32.store offset=12
    i32.const 0
    call $newQueue
    i32.store offset=1068
    local.get 1
    i32.const 0
    i32.store offset=24
    block  ;; label = @1
      loop  ;; label = @2
        local.get 1
        i32.load offset=24
        local.get 1
        i32.load offset=44
        i32.lt_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        local.get 1
        i32.const 1049
        i32.symbolic
        i32.store offset=36
        local.get 1
        i32.const 1044
        i32.symbolic
        i32.store offset=32
        local.get 1
        i32.load offset=20
        local.get 1
        i32.load offset=24
        i32.const 1
        i32.add
        local.get 1
        i32.load offset=36
        local.get 1
        i32.load offset=32
        call $createProcessToProcessor
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
    i32.const 0
    i32.store offset=24
    block  ;; label = @1
      loop  ;; label = @2
        local.get 1
        i32.load offset=24
        local.get 1
        i32.load offset=40
        i32.lt_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        local.get 1
        i32.const 1049
        i32.symbolic
        i32.store offset=36
        local.get 1
        i32.const 1044
        i32.symbolic
        i32.store offset=32
        local.get 1
        i32.const 1039
        i32.symbolic
        i32.store offset=28
        local.get 1
        i32.load offset=20
        local.get 1
        i32.load offset=36
        local.get 1
        i32.load offset=32
        local.get 1
        i32.load offset=28
        call $createProcessToProcess
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
    local.get 1
    i32.load offset=20
    local.get 0
    call $maxFlow
    i32.store
    i32.const 1054
    local.get 1
    call $printf
    drop
    i32.const 0
    i32.load offset=1064
    call $free
    i32.const 0
    i32.load offset=1068
    call $freeQueue
    local.get 1
    i32.load offset=20
    call $freeGraph
    local.get 1
    i32.load offset=16
    drop
    local.get 1
    i32.const 48
    i32.add
    global.set 0
    i32.const 0)
  (func $printf (type 7) (param i32 i32) (result i32)
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
  (func $malloc (type 0) (param i32) (result i32)
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
  (func $free (type 1) (param i32)
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
  (func $__WASP_alloc (type 7) (param i32 i32) (result i32)
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
  (func $__WASP_dealloc (type 1) (param i32)
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
  (func $__WASP_symb_int (type 0) (param i32) (result i32)
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
  (table (;0;) 1 1 funcref)
  (memory (;0;) 2)
  (global (;0;) (mut i32) (i32.const 66608))
  (export "memory" (memory 0))
  (export "__original_main" (func $__original_main))
  (data (;0;) (i32.const 1024) "tasks\00cost_com\00tmp3\00tmp2\00tmp1\00%d\0a\00")
  (data (;1;) (i32.const 1060) "0\04\01\00"))
