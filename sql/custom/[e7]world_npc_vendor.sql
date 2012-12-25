ALTER TABLE `npc_vendor`
  ADD COLUMN `group_id` INT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `ExtendedCost`;