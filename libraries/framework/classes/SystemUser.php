<?php
/**
 * Handles authentication and password handling for all city LDAP people.
 *
 * Applications should extend this class for their own users.  That way,
 * a city employee will have the same username and password on all applications.
 * Applications should use these public functions for their own users.
 *
 * @copyright 2006-2012 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
abstract class SystemUser extends ActiveRecord
{
	abstract public function getId();
	abstract public function getUsername();
	abstract public function getAuthenticationMethod();
	abstract public function getRoles();

	abstract public function hasRole($roles);

	abstract public function setAuthenticationMethod($method);
	abstract public function setRoles($roles);
	abstract public function setUsername($username);

	/**
	 * Passwords are set in clear text.  The only times you would want to set a password
	 * is when you're adding a new password or changing a person's password.
	 * Either way, it's up to the individual save routines to handle encrypting the new password
	 * before storing it.  Passwords should not be loaded in the constructor - they're
	 * supposed to be encrypted, so what's the point?
	 */
	abstract public function setPassword($password);

	/**
	 * Used to hand authentication off to the application
	 */
	abstract protected function authenticateDatabase($password);

	/**
	 * Used to hand password saving off to the application
	 */
	abstract protected function saveLocalPassword();

	/**
	 * Determines which authentication scheme to use for the user and calls the appropriate method
	 *
	 * @param string $password
	 * @return boolean
	 */
	public function authenticate($password)
	{
		switch($this->getAuthenticationMethod()) {
			case "local":
				return $this->authenticateDatabase($password);
			break;

			default:
				$type = $this->getAuthenticationMethod();
				return $type::authenticate($this->getUsername(),$password);
		}
	}

	/**
	 * Establishes a new Session and loads the default information for the user
	 */
	public function startNewSession()
	{
		session_destroy();
		session_start();

		$_SESSION['USER'] = $this;
		$_SESSION['IP_ADDRESS'] = $_SERVER['REMOTE_ADDR'];
	}

	/**
	 * Used to save passwords to the database
	 *
	 * Only local passwords should be saved.  External Identities should have
	 * their own methods for users to change passwords
	 */
	public function savePassword()
	{
		switch($this->getAuthenticationMethod()) {
			case "local":
				$this->saveLocalPassword();
			break;
		}
	}
}
