/*
 * Copyright 2009, Google Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


/**
 * @fileoverview  This file defines the VerticalPad class.
 */

/**
 * A Vertical Pad you can run on. These things oscillate between their starting
 * position and a z of 350"
 */
function VerticalPad(initObj) {
  this.absorbNamedValues(initObj);
  this.maxSpeed = 4;
  this.moveAmount = 4;
  this.bottomZ = this.z;
  this.topZ = 350;
  this.width = 42;
  this.height = 10;
}
VerticalPad.prototype = new Actor;

VerticalPad.prototype.onTick = function(timeElapsed) {
  // I bounce back and forth between the left and right points on my platform.
  if (this.z < this.bottomZ) {
    this.moveAmount += 1;
  } else if (this.z > this.topZ) {
    this.moveAmount -= 1;
  } else if (this.moveAmount >= 0) {
    this.moveAmount = this.maxSpeed;
  } else {
    this.moveAmount = -this.maxSpeed;
  }

  // I match my rotation to that of my platform.
  var myPlatform = world.platforms[this.platformID];
  this.rotZ = myPlatform.rotZ;


  this.z += this.moveAmount

  // If I collide with the avatar, then move the avatar along with me,
  // and set his "override" groundZ to be my own Z.
  if (this.collidesWith(avatar)) {
    if (avatar.velZ <= 0 && avatar.z >= this.z - 45) {
      avatar.z = this.z
      if (this.moveAmount < 0) {
        avatar.z += this.moveAmount;
      }
      avatar.groundZ = avatar.z;
    }
  }

  updateActor(this);
}
