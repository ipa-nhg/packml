/*
 * Software License Agreement (Apache License)
 *
 * Copyright (c) 2016 Shaun Edwards
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "packml_sm/transitions.h"
#include "packml_sm/events.h"
#include "packml_sm/dlog.h"

namespace packml_sm
{
CmdTransition::CmdTransition(const CmdEnum& cmd_value, const QString& name_value, PackmlState& from, PackmlState& to)
  : cmd(cmd_value), name(name_value)
{
  this->setTargetState(&to);
  from.addTransition(this);
  DLog::LogInfo("Creating %s transition from %s to %s", name.toStdString().c_str(), from.name().toStdString().c_str(),
                to.name().toStdString().c_str());
}

bool CmdTransition::eventTest(QEvent* e)
{
  //    ROS_INFO_STREAM("Testing event type: " << e->type());
  if (e->type() != QEvent::Type(PACKML_CMD_EVENT_TYPE))
    return false;
  CmdEvent* se = static_cast<CmdEvent*>(e);
  //    ROS_INFO_STREAM("Type cmd: " << cmd << ", event cmd: " << se->cmd);
  return (cmd == se->cmd);
}
}
